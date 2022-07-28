import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    allShares = db.execute("SELECT * FROM purchase WHERE user_id = (?) GROUP BY symbol", session["user_id"])
    sharesT = []
    gTotal = 0
    for row in allShares:
        symbol = row['symbol']
        name = lookup(symbol)['name']
        sumShares = db.execute("SELECT SUM(shares) FROM purchase WHERE symbol = (?)", symbol)
        price = usd(lookup(symbol)['price'])
        totalCash = usd(lookup(symbol)['price'] * sumShares[0]['SUM(shares)'])
        tLine = {
            "symbol": symbol,
            "name": name,
            "shares": sumShares[0]['SUM(shares)'],
            "price": price,
            "total": totalCash
        }
        gTotal = gTotal + lookup(symbol)['price'] * sumShares[0]['SUM(shares)']
        sharesT.append(tLine)
    balance = usd(db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])[0]['cash'])
    gTotal = usd(db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])[0]['cash'] + gTotal)
    return render_template("index.html", sharesT=sharesT, gTotal=gTotal, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares", type=int)
        if not lookup(request.form.get("symbol")):
            return apology("Invalid symbol", 400)
        elif not shares:
            return apology("Invalid number of shares", 400)
        elif shares < 1:
            return apology("Invalid number of shares", 400)
        symbol = request.form.get("symbol")
        price = lookup(symbol)['price']
        balance = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])
        balance1 = float(balance[0]['cash'])
        shares = request.form.get("shares")
        newBalance = balance1-float(price)*float(shares)
        user_id = session["user_id"]
        if price*float(shares) > balance1:
            return apology("Insufficient balance", 400)
        else:
            db.execute("CREATE TABLE IF NOT EXISTS purchase (id_purchase INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, symbol TEXT, price NUMERIC, shares INTEGER, time NUMERIC)")
            db.execute("INSERT INTO purchase (user_id, symbol, price, SHARES, time) VALUES (?,CURRENT_TIMESTAMP)",
                       (user_id, symbol, price, shares))
            db.execute("UPDATE users SET cash=(?) WHERE id=(?)", (newBalance), (user_id))
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    allShares = db.execute("SELECT * FROM purchase WHERE user_id = (?)", session["user_id"])
    historyT = []
    for row in allShares:
        symbol = row['symbol']
        name = lookup(symbol)['name']
        price = usd(row['price'])
        shares = row['shares']
        transacted = row['time']
        tLine = {
            "symbol": symbol,
            "name": name,
            "shares": shares,
            "price": price,
            "transacted": transacted
        }
        historyT.append(tLine)
    return render_template("history.html", historyT=historyT)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/changePassword", methods=["GET", "POST"])
@login_required
def changePassword():
    if request.method == "POST":
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("password_again"):
            return apology("passwords did not match", 403)
        elif not check_password_hash(rows[0]["hash"], request.form.get("password_existing")):
            return apology("Invalid password")
        else:
            db.execute("UPDATE users SET hash=(?) WHERE id=(?)", generate_password_hash(
                request.form.get("password")), session["user_id"])
            return redirect("/")
    else:
        return render_template("changePassword.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if lookup(request.form.get("symbol")):
            symbol = request.form.get("symbol")
            value = lookup(symbol)
            name = value['name']
            price = usd(value['price'])
            return render_template("quoted.html", name=name, symbol=symbol, price=price)
        else:
            return apology("Input not valid")
    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # Ensure passwords match
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords did not match", 400)
        elif db.execute("SELECT username FROM users WHERE username = (?)", (request.form.get("username"))):
            return apology("Username already exists", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (?)", (request.form.get(
                "username"), generate_password_hash(request.form.get("password"))))
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]
    else:
        return render_template("register.html")
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares", type=int)
        if not lookup(request.form.get("symbol")):
            return apology("Invalid symbol", 400)
        elif not shares:
            return apology("Invalid number of shares", 400)
        elif shares < 1:
            return apology("Invalid number of shares", 400)
        symbol = request.form.get("symbol")
        sumShares = db.execute("SELECT SUM(shares) FROM purchase WHERE symbol = (?)", symbol)[0]['SUM(shares)']
        if shares > sumShares:
            return apology("Invalid number of shares", 400)
        else:
            shares = float(shares) * (-1)
            user_id = session["user_id"]
            price = lookup(symbol)['price']
            balance = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])[0]['cash']
            newBalance = balance+price*shares*(-1)
            db.execute("INSERT INTO purchase (user_id, symbol, price, SHARES, time) VALUES (?,CURRENT_TIMESTAMP)",
                       (user_id, symbol, price, shares))
            db.execute("UPDATE users SET cash=(?) WHERE id=(?)", (newBalance), (user_id))
            return redirect("/")
    elif request.method == "GET":
        allShares = db.execute("SELECT * FROM purchase WHERE user_id = (?) GROUP BY symbol", session["user_id"])
        return render_template("sell.html", allShares=allShares)
