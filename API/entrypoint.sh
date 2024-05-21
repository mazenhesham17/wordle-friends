#!/bin/bash

# Check if the words file exists
if [ ! -f "words.csv" ]; then
  # Create the words file
  python3 prepare.py
fi

# Start the production server
gunicorn -w 4 -b 0.0.0.0:5000 app:app
