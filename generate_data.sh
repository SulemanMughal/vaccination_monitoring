#!/bin/bash

# Parameters
NUM_RECORDS=${1:-100}  # Default to 100 records if not specified
OUTPUT_FILE="inputRecords.txt"

# Sample data
FIRST_NAMES=("John" "Alice" "Bob" "Diana" "Eve" "Frank" "Grace" "Hank")
LAST_NAMES=("Smith" "Johnson" "Williams" "Brown" "Jones" "Miller" "Davis")
COUNTRIES=("Greece" "USA" "Germany" "France" "Italy" "Spain" "UK" "Canada")
VIRUSES=("COVID-19" "Influenza" "Polio" "Hepatitis-B")

# Helper function to generate random date
generate_random_date() {
  YEAR=$((RANDOM % 3 + 2022))  # Between 2022 and 2024
  MONTH=$((RANDOM % 12 + 1))
  DAY=$((RANDOM % 28 + 1))
  printf "%04d-%02d-%02d" $YEAR $MONTH $DAY
}

# Main loop
echo -n "" > "$OUTPUT_FILE"  # Clear the file
for ((i = 0; i < NUM_RECORDS; i++)); do
  ID=$((RANDOM % 10000))
  FIRST=${FIRST_NAMES[$RANDOM % ${#FIRST_NAMES[@]}]}
  LAST=${LAST_NAMES[$RANDOM % ${#LAST_NAMES[@]}]}
  COUNTRY=${COUNTRIES[$RANDOM % ${#COUNTRIES[@]}]}
  AGE=$((RANDOM % 83 + 18))  # Age between 18 and 100
  VIRUS=${VIRUSES[$RANDOM % ${#VIRUSES[@]}]}
  VACCINATED=$((RANDOM % 2))

  if [ "$VACCINATED" -eq 1 ]; then
    DATE=$(generate_random_date)
    echo "$ID $FIRST $LAST $COUNTRY $AGE $VIRUS YES $DATE" >> "$OUTPUT_FILE"
  else
    echo "$ID $FIRST $LAST $COUNTRY $AGE $VIRUS NO" >> "$OUTPUT_FILE"
  fi
done

echo "Generated $NUM_RECORDS records in $OUTPUT_FILE"
