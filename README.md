# Vaccination Monitoring System

A C-based command-line application designed to efficiently manage and monitor vaccination records using advanced data structures like Bloom Filters and Skip Lists.

## Objectives

* **Efficient Data Management**: Implement data structures that allow for quick insertion, deletion, and lookup of vaccination records.
* **Scalability**: Ensure the system can handle large datasets without significant performance degradation.
* **Modularity**: Design the system with modular components for ease of maintenance and potential future enhancements.
* **User-Friendly Interface**: Provide a straightforward command-line interface for users to interact with the system.

## Technologies Used

* **Programming Language**: C
* **Data Structures**:

  * **Bloom Filter**: A space-efficient probabilistic data structure used to test whether an element is a member of a set.
  * **Skip List**: A data structure that allows fast search within an ordered sequence of elements.
* **Build System**: Makefile for compiling the project.([GitHub][1])

## Features

* **Record Management**:

  * Add new vaccination records.
  * Search for existing records.
  * Delete records as needed.
* **Data Validation**: Ensure that input data adheres to expected formats and constraints.
* **Performance Optimization**: Utilize Bloom Filters for quick membership tests and Skip Lists for efficient data retrieval.([Jotform][2])

## Applications

This system is suitable for:

* **Healthcare Facilities**: Managing patient vaccination records efficiently.
* **Research Institutions**: Handling large datasets related to vaccination studies.
* **Educational Purposes**: Demonstrating the practical applications of data structures in real-world scenarios.([Jotform][2], [The Official Microsoft Blog][3])

## Future Enhancements

* **GUI Integration**: Develop a graphical user interface for improved user interaction.
* **Database Connectivity**: Integrate with databases like MySQL or PostgreSQL for persistent storage.
* **Web-Based Interface**: Create a web application version for remote access and management.
* **Advanced Reporting**: Implement features to generate detailed reports and analytics.

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/SulemanMughal/vaccination_monitoring.git
   cd vaccination_monitoring
   ```

2. **Compile the Project**:

   ```bash
   make
   ```

3. **Run the Application**:

   ```bash
   ./vaccinationMonitor
   ```

## Contributing

Contributions are welcome! If you would like to contribute to this project, feel free to fork the repository, make your changes, and submit a pull request.

