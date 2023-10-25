// script.js

  // Function to handle button clicks and redirect to the specified page
  function redirectTo(page) {
    window.location.href = page;
  }
  

document.addEventListener("DOMContentLoaded", function() {

  // Event listener for the connection form submission
  document.getElementById("connectionForm").addEventListener("submit", function(event) {
    event.preventDefault();

    var ssid = document.getElementById("fname").value;
    var password = document.getElementById("lname").value;

    // Assuming you have a function to handle form submission and return an IP
    var ipAddress = submitFormAndReturnIP(ssid, password);

    // Display the returned IP address
    document.getElementById("ipDisplay").value = ipAddress;
  });

  // This function is just a placeholder. Replace it with your actual form submission logic.
  function submitFormAndReturnIP(ssid, password) {
    // Perform your form submission logic here, and return the obtained IP address.
    // For demonstration purposes, let's assume you have a function that returns a static IP.
    return "192.168.1.100";
  }

  // Function to handle the "Add" button click in the scheduler
  document.getElementById("addButton").addEventListener("click", function() {
    // Get selected values for hour, minute, and AM/PM
    var selectedHour = document.getElementById("hour-dd").value;
    var selectedMinute = document.getElementById("minute-dd").value;
    var selectedAmPm = document.getElementById("ampm-dd").value;

    // Do something with the selected values (you can customize this part)
    console.log("Selected Hour: " + selectedHour);
    console.log("Selected Minute: " + selectedMinute);
    console.log("Selected AM/PM: " + selectedAmPm);
  });

  // Function to handle the "TEST" button click in the scheduler
  document.getElementById("testButton").addEventListener("click", function() {
    // Get the value entered in the input for the amount to feed
    var amountToFeed = document.getElementById("amountToFeed").value;

    // Do something with the entered amount (you can customize this part)
    console.log("Amount to Feed: " + amountToFeed);
  });

  // Function to handle the "SAVE" button click in the scheduler
  document.getElementById("saveButton").addEventListener("click", function() {
    // Perform actions to save the scheduler settings (you can customize this part)
    console.log("Scheduler settings saved!");
  });
});
