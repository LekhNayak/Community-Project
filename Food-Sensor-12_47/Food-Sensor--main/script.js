document.addEventListener('DOMContentLoaded', () => {
  // Replace with your actual ThingSpeak Channel ID and Read API Key
  const channelId = '2599999';
  const apiKey = 'SX2MQRH2IHLWECII';

  // Function to fetch sensor data from ThingSpeak API
  async function fetchSensorData() {
    const url = `https://api.thingspeak.com/channels/${channelId}/feeds.json?api_key=${apiKey}&results=1`;

    try {
      const response = await fetch(url);
      const data = await response.json();
      let phsensor = data.feeds[0].field1;
      let color = data.feeds[0].field2;
      let turb = data.feeds[0].field3;
      let methane = data.feeds[0].field4;
      let alcohol = data.feeds[0].field5;

      document.querySelector("#turbidity").innerHTML = `${turb}`;
      document.querySelector("#phsensor").innerHTML = `${phsensor}`;
      document.querySelector("#colorsensor").innerHTML = `${color}`;
      document.querySelector("#methane").innerHTML = `${methane}`;
      document.querySelector("#alcohol").innerHTML = `${alcohol}`;

      console.log(data.feeds[0]);
    } catch (error) {
      console.error("Error fetching data:", error);
    }
  }

  // Fetch data every 15 seconds
  setInterval(fetchSensorData, 1000);

  // Initial call to fetch data immediately when the page loads
  fetchSensorData();
});
