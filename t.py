import speech_recognition as sr

r = sr.Recognizer()
mic = sr.Microphone()

with mic as source:
    print("Calibrating mic... (1 second)")
    r.adjust_for_ambient_noise(source, duration=1)

print("Start speaking (Ctrl+C to stop):")

try:
    while True:
        with mic as source:
            print("Listening...")
            audio = r.listen(source)

        try:
            text = r.recognize_google(audio, language="en-US")
            print("You said:", text)
        except sr.UnknownValueError:
            print("Didn't catch that, please repeat...")
        except sr.RequestError as e:
            print("API error:", e)
            break

except KeyboardInterrupt:
    print("\nStopped listening.")
