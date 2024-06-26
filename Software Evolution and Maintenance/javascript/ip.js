fetch('https://api.ipify.org?format=json')
  .then(response => response.json())
  .then(data => {
    const ipAddress = data.ip;
    console.log('Your IP address is:', ipAddress);
    const ipDisplayElement = document.getElementById('ip-address-display');
        ipDisplayElement.textContent = `Your IP Address: ${ipAddress}`;
  })
  .catch(error => {
    console.error('Error fetching IP:', error);
  });