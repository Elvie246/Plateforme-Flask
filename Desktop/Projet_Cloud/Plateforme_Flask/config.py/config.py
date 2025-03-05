import os

class Config:
    # Configuration de Flask
    DEBUG = True
    SECRET_KEY = os.getenv("SECRET_KEY", "super_secret_key")

    # Configuration Azure Blob Storage
    AZURE_STORAGE_CONNECTION_STRING = os.getenv("AZURE_STORAGE_CONNECTION_STRING", "votre_chaîne_de_connexion")
    AZURE_CONTAINER_NAME = os.getenv("AZURE_CONTAINER_NAME", "votre_conteneur")
    AZURE_BLOB_NAME = "tasks.json"  # Nom du fichier JSON stocké sur Azure
