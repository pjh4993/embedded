from flask import Flask, render_template, request
import threading
import sub

app = Flast(__name__)

@app.route('/')
def main_page():
    return render_template("main.html", cnt0=sub.cnt0, cnt1=sub.cnt1) 

@app.route('/reset') 
def reset():
    sub.cnt0 = 0
    sub.cnt1 = 0
    return render_template("main.html", cnt0=sub.cnt0, cnt1=sub.cnt1) 

