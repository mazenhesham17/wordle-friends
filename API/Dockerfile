# Docker file for Word Service API
FROM python:3.8-slim

# Set the working directory
WORKDIR /app

# Copy the requirements file
COPY requirements.txt /app

# Install any needed packages specified in requirements.txt
RUN pip install -r requirements.txt

# Copy the current directory contents into the container at /app
COPY . /app

# make the entrypoint.sh file executable
RUN chmod +x entrypoint.sh

# Expose the port the app runs on
EXPOSE 5000

ENTRYPOINT ["./entrypoint.sh"]