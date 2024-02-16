import pandas as pd

import json

filepath = 'wordsapi_sample.json'

with open(filepath, 'r') as f:
    data = json.load(f)

words = list(data.keys())

words = [ word for word in words if len(word) == 5 and word.isalpha()]

words = pd.DataFrame(words, columns=['word'])

words.to_csv('words.csv', index=False)