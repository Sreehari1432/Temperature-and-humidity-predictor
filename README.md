# 🌡️ Temperature and Humidity Predictor Using XGBoost

A real-time, AI-powered web platform for predicting and monitoring **temperature** and **humidity** using IoT and **machine learning**.  
The system integrates a **DHT11 sensor**, **ESP32**, **Blynk Cloud**, **Google Apps Script**, and **XGBoost** to deliver accurate environmental forecasts through a user-friendly web dashboard.

▶️ [Watch Demo Video](https://github.com/rahul5383/Miniproject-iot/blob/main/working_video.mp4)

---

## 🛠 Features
- **Real-time Monitoring**: DHT11 sensor + ESP32 send live readings to Blynk Cloud and LCD.
- **Predictive Analytics**: Forecasts future temperature and humidity trends using a trained XGBoost model.
- **Cloud Data Storage**: Readings automatically logged to **Google Sheets** via **Apps Script**.
- **Web Dashboard**: Built with **Flask**, **HTML/CSS**, and **Chart.js** for visualization.
- **User-friendly Interface**: Easily access live values, predictions, and analytics through a simple web UI.

---

## 📋 System Architecture

- **Data Collection**:  
  - DHT11 sensor reads temperature and humidity.
  - ESP32 sends real-time data to **Blynk Cloud** and displays it on a **16x2 LCD**.

- **Data Storage**:  
  - Google Apps Script auto-logs readings into **Google Sheets** for future processing.

- **Model Training and Prediction**:  
  - Historical IoT data + Kaggle dataset are used to train an **XGBoost** model for accurate forecasting.
  
- **Web Application**:  
  - Built using **Flask**, **HTML**, **TailwindCSS**, and **Chart.js**.
  - Pages: **Home**, **Analytics**, **Predictions**.

---

## 📈 Screenshots

![IoT Setup](https://github.com/rahul5383/Miniproject-iot/blob/main/Iot_setup.jpg)

## 🔧 Tech Stack

- **Hardware**:
  - ESP32 Microcontroller
  - DHT11 Temperature & Humidity Sensor
  - LCD Display (16x2, I2C)
  - Wi-Fi Network
  
- **Software**:
  - Arduino IDE, C++ 
  - Flask 
  - HTML/CSS, TailwindCSS (Frontend)
  - Chart.js , matplotlib (Graphs & Charts)
  - Blynk 2.0 Cloud IoT Platform (Real-time cloud storage)
  - Google Apps Script (Data logging automation)
  - XGBoost, Scikit-learn, tensorflow ,keras (Machine Learning)

---

## 🚀 Getting Started

### Hardware Setup:
1. Connect DHT11 sensor to ESP32 (data pin to GPIO).
2. Set up LCD display using I2C connection.
3. Flash the ESP32 using Arduino IDE with the sensor data upload code.
4. Link ESP32 with **Blynk Cloud** using authentication tokens.


