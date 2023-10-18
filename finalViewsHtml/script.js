// script.js

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
