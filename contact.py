import json
import os

CONTACTS_FILE = 'contacts.json'

def load_contacts():
    if not os.path.exists(CONTACTS_FILE):
        return []
    with open(CONTACTS_FILE, 'r') as file:
        return json.load(file)

def save_contacts(contacts):
    with open(CONTACTS_FILE, 'w') as file:
        json.dump(contacts, file, indent=4)

def add_contact(name, phone, email):
    contacts = load_contacts()
    contacts.append({'name': name, 'phone': phone, 'email': email})
    save_contacts(contacts)
    print(f"Contact '{name}' added.")

def list_contacts():
    contacts = load_contacts()
    if not contacts:
        print("No contacts found.")
        return
    for i, c in enumerate(contacts, 1):
        print(f"{i}. {c['name']} - {c['phone']} - {c['email']}")

def main():
    while True:
        print("\nContact List")
        print("1. Add Contact")
        print("2. View Contacts")
        print("3. Exit")
        choice = input("Enter your choice: ")
        
        if choice == '1':
            name = input("Name: ")
            phone = input("Phone: ")
            email = input("Email: ")
            add_contact(name, phone, email)
        elif choice == '2':
            list_contacts()
        elif choice == '3':
            break
        else:
            print("Invalid choice, try again.")

if __name__ == "__main__":
    main()