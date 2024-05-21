# Docker file for Frontend
FROM node:19.5.0-alpine

# Set the working directory
WORKDIR /app

# Copy the packages files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the current directory contents into the container at /app
COPY . /app

# Build the app
RUN npm run build

# Expose the port the app runs on
EXPOSE 3000

# Serve the app
CMD ["npm", "start"]