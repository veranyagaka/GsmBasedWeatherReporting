#!/bin/bash

# Initialize a Git repository in the current directory
git init

# Add the README.md file to the staging area
git add .

# Commit the changes with a message "first commit"
git commit -m "initial setup"

# Rename the main branch to main (assuming it's currently named master)
git branch -M main

# Add a remote repository named origin with the URL provided
git remote add origin https://github.com/veranyagaka/GsmBasedWeatherReporting.git

# Push all commits to the remote repository's main branch and configure 
# upstream tracking so future pushes can use 'git push' shorthand
git push -u origin main

echo "Git repository initialized and pushed to remote!"

