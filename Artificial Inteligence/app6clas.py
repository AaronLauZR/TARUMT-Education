#!/usr/bin/env python
# coding: utf-8

# In[1]:


import streamlit as st
import tensorflow as tf
from keras.models import load_model
from tensorflow.keras.preprocessing.image import load_img, img_to_array
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
import numpy as np
from io import BytesIO
from PIL import Image

# Load the OCR model
MN_load_model = load_model("mobileNet_model_6class.h5")

# Define the OCR function
def ocr(image):
    img = load_img(image, target_size=(224, 224))
    img = img_to_array(img)
    img = np.expand_dims(img, axis=0)
    img = tf.keras.applications.mobilenet.preprocess_input(img)
    prediction = MN_load_model.predict(img)
    result = np.argmax(prediction)
    return result

# Define the Streamlit app
def app():
    st.title("OCR with Streamlit")
    image_file = st.file_uploader("Upload an image", type=["jpg", "jpeg", "png"])
    if image_file is not None:
        image_bytes = image_file.read()
        image = Image.open(BytesIO(image_bytes))
        # Resize the image to a smaller size
        image = image.resize((20, 20))
        st.image(image, caption='Uploaded Image')
        result = ocr(BytesIO(image_bytes))
        if result == 0:
            st.write("Predicted text: One")
        elif result == 1:
            st.write("Predicted text: Two")
        elif result == 2:
            st.write("Predicted text: Three")
        elif result == 3:
            st.write("Predicted text: Four")
        elif result == 4:
            st.write("Predicted text: Five")
        elif result == 5:
            st.write("Predicted text: Six")
        else:
            st.write("Error: Invalid prediction")

if __name__ == "__main__":
    app()


# In[ ]:




