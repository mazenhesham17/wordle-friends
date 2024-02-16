import pandas as pd
import random
from flask import Flask, request, jsonify

app = Flask(__name__)

words = pd.read_csv('words.csv').values
LEN = words.shape[0]

@app.route('/wordle', methods=['GET'])
def wordle():
    word = words[random.randint(0, LEN)][0]
    return jsonify({'word': word})

if __name__ == '__main__':
    app.run(debug=True)