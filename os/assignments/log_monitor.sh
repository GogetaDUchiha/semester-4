#!/bin/bash

# Check if log file path is provided
if [ -z "$1" ]; then
  echo "Usage: $0 /path/to/logfile"
  exit 1
fi

LOG_FILE="$1"
BACKUP_DIR="./log_backups"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
ALERT_THRESHOLD=5  # Threshold for brute-force attempt
ALERT_LOG="./suspicious_activity_$TIMESTAMP.log"

# Create backup directory if not exists
mkdir -p "$BACKUP_DIR"

# Backup the log file
cp "$LOG_FILE" "$BACKUP_DIR/$(basename "$LOG_FILE")_$TIMESTAMP"

# Find failed login attempts
echo "Checking for failed login attempts..."
FAILED_LOGINS=$(grep -E "Failed password|authentication failure" "$LOG_FILE")

if [ -n "$FAILED_LOGINS" ]; then
  echo "$FAILED_LOGINS" > "$ALERT_LOG"

  echo -e "\nRepeated failed attempts by IP:"
  echo "$FAILED_LOGINS" | grep -oE 'from [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+' | awk '{print $2}' \
    | sort | uniq -c | sort -nr | tee -a "$ALERT_LOG"

  echo -e "\nRepeated failed attempts by user:"
  echo "$FAILED_LOGINS" | grep -oP "user \K\S+" \
    | sort | uniq -c | sort -nr | tee -a "$ALERT_LOG"

  # Detect brute-force attacks
  echo -e "\nChecking for brute-force attempts..."
  echo "$FAILED_LOGINS" | grep -oE 'from [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+' \
    | awk '{print $2}' | sort | uniq -c | awk -v threshold="$ALERT_THRESHOLD" '$1 >= threshold' \
    | while read count ip; do
      echo "Potential brute-force attack from $ip with $count failed attempts." | tee -a "$ALERT_LOG"
    done

  echo -e "\nALERT: Suspicious activity found. See log: $ALERT_LOG"
else
  echo "No suspicious activity found."
fi
