import pandas as pd
import numpy as np
import pickle
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler

with open("xgb_temp_new.pkl", "rb") as f:
    xgb_temp = pickle.load(f)

with open("xgb_humid_new.pkl", "rb") as f:
    xgb_humid = pickle.load(f)

df = pd.read_csv("data_esp32.csv") 

df['date'] = pd.to_datetime(df['date'])

temp_feature = 'apparent_temperature'
humid_feature = 'relative_humidity_2m'

scaler_temp = MinMaxScaler()
scaler_humid = MinMaxScaler()

df['temp_scaled'] = scaler_temp.fit_transform(df[[temp_feature]])
df['humid_scaled'] = scaler_humid.fit_transform(df[[humid_feature]])

def create_sequences(data, seq_length):
    X = []
    for i in range(len(data) - seq_length):
        X.append(data[i:i + seq_length])
    return np.array(X)

seq_length = 24 

X_temp = create_sequences(df['temp_scaled'].values, seq_length)
X_humid = create_sequences(df['humid_scaled'].values, seq_length)

y_pred_temp = xgb_temp.predict(X_temp)
y_pred_humid = xgb_humid.predict(X_humid)

y_pred_temp_actual = scaler_temp.inverse_transform(y_pred_temp.reshape(-1, 1))
y_pred_humid_actual = scaler_humid.inverse_transform(y_pred_humid.reshape(-1, 1))

actual_temp = df[temp_feature].iloc[seq_length:].values
actual_humid = df[humid_feature].iloc[seq_length:].values
dates = df['date'].iloc[seq_length:].values  

results = pd.DataFrame({
    "Date": dates,
    "Actual Temperature": actual_temp,
    "Predicted Temperature": y_pred_temp_actual.flatten(),
    "Actual Humidity": actual_humid,
    "Predicted Humidity": y_pred_humid_actual.flatten(),
})

results.to_csv("predicted_vs_actual.csv", index=False)

plt.figure(figsize=(12, 5))

plt.subplot(2, 1, 1)
plt.plot(results["Date"], results["Actual Temperature"], label="Actual Temperature", color="blue")
plt.plot(results["Date"], results["Predicted Temperature"], label="Predicted Temperature", color="red", linestyle="dashed")
plt.xlabel("Date")
plt.ylabel("Temperature (°C)")
plt.title("Predicted vs Actual Temperature")
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(results["Date"], results["Actual Humidity"], label="Actual Humidity", color="green")
plt.plot(results["Date"], results["Predicted Humidity"], label="Predicted Humidity", color="orange", linestyle="dashed")
plt.xlabel("Date")
plt.ylabel("Humidity (%)")
plt.title("Predicted vs Actual Humidity")
plt.legend()

plt.tight_layout()
plt.show()

print("Predictions and actual values saved to predicted_vs_actual.csv!")
