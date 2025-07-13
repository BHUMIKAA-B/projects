import speech_recognition as sr
import pyttsx3
import pywhatkit
import datetime
import wikipedia

# Initialize speech engine
engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[1].id)  # Female voice (index 1)

def talk(text):
    engine.say(text)
    engine.runAndWait()

def greet():
    hour = datetime.datetime.now().hour
    if hour < 12:
        talk("Good morning!")
    elif hour < 18:
        talk("Good afternoon!")
    else:
        talk("Good evening!")
    talk("I am . How can I assist you today?")

def take_command():
    listener = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening... (Say something after the beep)")
        talk("Listening now. Please speak...")
        listener.pause_threshold = 1  # Waits for 1 second of silence before processing
        audio = listener.listen(source, timeout=5, phrase_time_limit=8)

    try:
        command = listener.recognize_google(audio)
        command = command.lower()
        if 'pari' in command:
            command = command.replace('pari', '')
        print(f"You said: {command}")
    except sr.UnknownValueError:
        print("Could not understand audio")
        talk("Sorry, I didn't catch that.")
        return ""
    except sr.RequestError:
        print("API unavailable")
        talk("Sorry, I'm having trouble connecting to the service.")
        return ""
    
    return command


def run_pari():
    greet()
    while True:
        command = take_command()

        if 'play' in command:
            song = command.replace('play', '')
            talk(f"Playing {song}")
            pywhatkit.playonyt(song)
            break
        elif 'search' in command:
            query = command.replace('search', '').strip()
            talk(f"Searching for {query} on Google.")
            pywhatkit.search(query)

        elif 'time' in command:
            time = datetime.datetime.now().strftime('%I:%M %p')
            talk(f"The current time is {time}")

        elif 'who is' in command or 'what is' in command:
            try:
                topic = command.replace('who is', '').replace('what is', '').strip()
                talk(f"Let me look up {topic} on Wikipedia.")
                info = wikipedia.summary(topic, sentences=2, auto_suggest=False, redirect=True)
                print(info)
                talk(info)
            except wikipedia.exceptions.DisambiguationError as e:
                talk("That topic has multiple results. Can you please be more specific?")
                print("Disambiguation options:", e.options)
            except wikipedia.exceptions.PageError:
                talk("Sorry, I couldn't find any information on that topic.")
            except Exception as e:
                print("Wikipedia Error:", e)
                talk("Something went wrong while searching. Please try again.")

        elif 'date' in command:
            today = datetime.date.today()
            talk(f"Today's date is {today.strftime('%B %d, %Y')}")

        elif 'exit' in command or 'stop' in command:
            talk("Goodbye! Have a great day!")
            break

        else:
            talk("Sorry, I didn't get that. Could you please repeat?")

# Start the assistant
run_pari()
