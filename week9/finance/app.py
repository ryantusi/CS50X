import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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

    # Store current user details
    user_id = session["user_id"]
    row = db.execute("SELECT username, cash FROM users WHERE id = ?", user_id)
    user_name = str(row[0]["username"])
    user_cash = round(float(row[0]["cash"]), 2)

    # Delete rows from portfolios table of current user if shares are 0
    db.execute("DELETE FROM portfolios WHERE user_id = ? AND shares = 0;", user_id)

    # Get portfolio of current user
    PORTFOLIO = db.execute(
        "SELECT stock, shares FROM portfolios WHERE user_id = ?;", user_id
    )

    # Computing grand total and total valuation
    grand_total = user_cash
    valuation_total = 0

    # Getting current price of stocks owned by current user and append price and valuation to the PORTFOLIO dictionary
    for val in PORTFOLIO:
        stock = val["stock"]
        shares = val["shares"]
        stock = lookup(stock)
        stock_price = stock["price"]
        val["price"] = usd(stock_price)
        valuation = stock_price * shares
        val["valuation"] = usd(valuation)
        valuation_total += valuation

    # Computing and rounding grand total and total valuation
    grand_total += valuation_total
    grand_total = round(grand_total, 2)
    valuation_total = round(valuation_total, 2)

    # rendering the homepage with portfolio table
    return render_template(
        "layout.html",
        name=user_name,
        id=user_id,
        portfolio=PORTFOLIO,
        balance=user_cash,
        valuation=valuation_total,
        total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol is submitted
        if not request.form.get("symbol"):
            return apology("must provide Stock Symbol", 400)

        # Ensure shares are submitted and store it variable
        if not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        # storing symbol
        stock = request.form.get("symbol")

        # Ensure shares are positive
        shares = request.form.get("shares")

        # using lookup() to call API search on symbol provided
        stock_list = lookup(stock)

        # Ensure details are returned from API call
        if stock_list == None:
            return apology("No such symbol/stock", 400)

        # Ensure shares are convertable to int
        try:
            shares = int(shares)
        except:
            return apology("An error occured", 400)

        # Ensure shares are positive number
        if shares <= 0:
            return apology("must provide positive number of shares", 400)

        # Store user ID
        user = session["user_id"]

        # Stor user cash
        row = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = row[0]["cash"]

        # Store stock name and price
        if stock_list != None:
            stock_name = str(stock_list["symbol"])
            stock_price = float(stock_list["price"])

        # Compute total price
        total_price = float(stock_price * shares)

        # Ensure enough cash to buy shares
        if cash < total_price:
            return apology("Low Cash Balance", 400)

        # Update database of transactions and users table
        db.execute(
            "INSERT INTO transactions (user_id, stock, price, shares, type) VALUES (?, ?, ?, ?, 'BUY');",
            user,
            stock_name,
            stock_price,
            shares,
        )
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?;", total_price, user)

        # Update database of portfolios table for current user
        row = db.execute(
            "SELECT stock, shares FROM portfolios WHERE user_id = ? AND stock = ?;",
            user,
            stock_name,
        )

        # If new stock
        if len(row) == 0:
            db.execute(
                "INSERT INTO portfolios (user_id, stock, shares) VALUES (?, ?, ?)",
                user,
                stock_name,
                shares,
            )

        # If already has stock, update number of shares
        elif len(row) == 1:
            db.execute(
                "UPDATE portfolios SET shares = shares + ? WHERE user_id = ? AND stock = ?",
                shares,
                user,
                stock_name,
            )

        # Successful session and redirect to homepage
        return redirect("/")
    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get all transactions of current user from transactions table
    user_id = session["user_id"]
    TRANSACTIONS = db.execute("SELECT * FROM transactions WHERE user_id = ?;", user_id)

    # Render it to the html
    return render_template("history.html", transactions=TRANSACTIONS)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reaches route via POST
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide Stock Symbol", 400)

        # storing symbol
        stock = request.form.get("symbol")

        # using lookup() to call API search on symbol provided
        stock_list = lookup(stock)

        # Ensure details are returned from API call
        if stock_list == None:
            return apology("No such symbol/stock", 400)

        # using usd() to insert $ symbol in price
        stock_list["price"] = usd(stock_list["price"])

        # successful rendering
        return render_template("quoted.html", stocks=stock_list)

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via POST
    if request.method == "POST":
        # Storing variables
        user = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # checking for rows with username
        rows = db.execute("SELECT * FROM users WHERE username = ?;", user)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure username does not exist
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Ensure matching password and confirmation, then create a hash value for password
        if password != confirmation:
            return apology("passwords do not match", 400)
        else:
            hash = generate_password_hash(password, method="pbkdf2", salt_length=16)

        # Ensure all conditions meet, then insert username and hash to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", user, hash)

        # start session for the new user
        rows = db.execute("SELECT * FROM users WHERE username = ?;", user)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get current user details and portfolio
    user_id = session["user_id"]
    rows = db.execute(
        "SELECT stock, shares FROM portfolios WHERE user_id = ?;", user_id
    )
    STOCKS = []
    for val in rows:
        STOCKS.append(val["stock"])

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure Symbol was submitted
        sym = request.form.get("symbol")
        if not sym:
            return apology("Select owned stock", 400)

        if sym not in STOCKS:
            return apology("Select owned stock", 400)

        # Ensure correct number of shares were submitted
        shares = int(request.form.get("shares"))
        current_shares = 0
        for val in rows:
            if val["stock"] == sym:
                current_shares = int(val["shares"])

        # Ensure correct Number of shares were submitted
        if not shares:
            return apology("Enter shares", 400)

        if shares <= 0 or shares > current_shares:
            return apology("You don't have enough shares / Enter positive number", 400)

        # Ensure database was updated with transactions table
        current_stock = lookup(sym)
        price = current_stock["price"]
        db.execute(
            "INSERT INTO transactions (user_id, stock, price, shares, type) VALUES (?, ?, ?, ?, 'SELL');",
            user_id,
            sym,
            price,
            shares,
        )

        # Ensure database was updated with user table
        result = price * shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;", result, user_id)

        # Ensure database was updates with portfolio table
        db.execute(
            "UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND stock = ?;",
            shares,
            user_id,
            sym,
        )

        # Successful session
        return redirect("/")

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("sell.html", stocks=STOCKS)
