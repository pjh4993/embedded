from flask import Flask, render_template, request
import threading
import sub

app = Flask(__name__)

@app.route('/')
def main_page():
    print (sub.cnt0)
    print (sub.cnt1)
    return render_template("main.html", cnt0=sub.cnt0, cnt1=sub.cnt1) 

@app.route('/reset') 
def reset():
    sub.cnt0 = 0
    sub.cnt1 = 0
    return render_template("main.html", cnt0=sub.cnt0, cnt1=sub.cnt1) 

if __name__ == "__main__" :
    app.run(host = "0.0.0.0", debug = True)
