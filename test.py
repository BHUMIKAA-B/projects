import speech_recognition as sr
import pywhatkit
import datetime
import wikipedia
from deep_translator import GoogleTranslator
from gtts import gTTS
import pygame
import os
import time

# Initialize pygame
pygame.init()
pygame.mixer.init()

# Speak Kannada from English text
def talk_kannada(text_en):
    try:
        translated_kn = GoogleTranslator(source='en', target='kn').translate(text_en)
        print("Pari (Kannada):", translated_kn)
        filename = "response_kn.mp3"

        # Clean up any old audio
        if os.path.exists(filename):
            try:
                pygame.mixer.music.stop()
                pygame.mixer.quit()
                os.remove(filename)
            except Exception as e:
                print("Delete error:", e)

        # Generate and save audio
        tts = gTTS(text=translated_kn, lang='kn')
        tts.save(filename)

        # Play audio
        pygame.mixer.init()
        pygame.mixer.music.load(filename)
        pygame.mixer.music.play()

        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)

        # Remove audio file after playing
        os.remove(filename)

    except Exception as e:
        print("Kannada Voice Error:", e)

# Greeting and introduction
def greet():
    hour = datetime.datetime.now().hour
    if hour < 12:
        talk_kannada("Good morning!")
    elif hour < 18:
        talk_kannada("Good afternoon!")
    else:
        talk_kannada("Good evening!")

    time.sleep(1)
    talk_kannada("I am Pari, your Kannada voice assistant.")
    time.sleep(1.5)
    talk_kannada("You can ask me to tell the time, date, play a song, or search on Wikipedia.")
    time.sleep(2)

# Take user's command in Kannada and translate to English
def take_command():
    recognizer = sr.Recognizer()
    talk_kannada("Please speak now.")  # Kannada: ದಯವಿಟ್ಟು ಮಾತನಾಡಿ
    time.sleep(1)

    with sr.Microphone() as source:
        print("🎤 Listening...")
        recognizer.pause_threshold = 1

        try:
            audio = recognizer.listen(source, timeout=5, phrase_time_limit=8)
            print("🔊 Audio captured...")
            command_kn = recognizer.recognize_google(audio, language='kn')
            print("📥 Kannada Recognized:", command_kn)

            command_en = GoogleTranslator(source='kn', target='en').translate(command_kn)
            print("🌐 Translated to English:", command_en)

            return command_en.lower()

        except sr.UnknownValueError:
            print("⚠️ Speech not recognized")
            talk_kannada("Sorry, I didn't understand.")
        except sr.RequestError:
            print("⚠️ Speech API error")
            talk_kannada("There was a network issue.")
        except Exception as e:
            print("⚠️ Error:", e)
            talk_kannada("Something went wrong.")
        return ""

# Assistant logic
def run_pari():
    greet()
    while True:
        command = take_command()
        if not command:
            continue

        if 'play' in command:
            song = command.replace('play', '').strip()
            talk_kannada(f"Playing {song} on YouTube.")
            pywhatkit.playonyt(song)
            break

        elif 'search' in command:
            query = command.replace('search', '').strip()
            talk_kannada(f"Searching for {query}.")
            pywhatkit.search(query)

        elif 'time' in command:
            current_time = datetime.datetime.now().strftime('%I:%M %p')
            talk_kannada(f"The current time is {current_time}.")

        elif 'date' in command:
            today = datetime.date.today()
            talk_kannada(f"Today's date is {today.strftime('%B %d, %Y')}.")

        elif 'who is' in command or 'what is' in command:
            try:
                topic = command.replace('who is', '').replace('what is', '').strip()
                talk_kannada(f"Searching Wikipedia for {topic}.")
                info = wikipedia.summary(topic, sentences=2)
                print("Wikipedia:", info)
                talk_kannada(info)
            except wikipedia.exceptions.DisambiguationError:
                talk_kannada("That topic has many meanings. Please be more specific.")
            except wikipedia.exceptions.PageError:
                talk_kannada("I couldn't find any information on that.")
            except Exception as e:
                print("Wikipedia Error:", e)
                talk_kannada("Something went wrong while searching.")

        elif 'exit' in command or 'stop' in command:
            talk_kannada("Goodbye! Have a great day.")
            break

        else:
            talk_kannada("Sorry, I didn’t get that. Please repeat.")

# Run Pari
run_pari()
