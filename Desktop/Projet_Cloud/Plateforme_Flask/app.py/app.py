from flask import Flask, jsonify, request, abort
#from azure.storage.blob import BlobServiceClient
import json
import os
from datetime import datetime
#from config import Config  # Importation de la configuration

# Initialisation de l'application Flask
app = Flask(__name__)
app.config.from_object(Config)  # Charger la configuration

# Configuration Azure Blob Storage
CONNECTION_STRING = app.config["AZURE_STORAGE_CONNECTION_STRING"]
CONTAINER_NAME = app.config["AZURE_CONTAINER_NAME"]
BLOB_NAME = app.config["AZURE_BLOB_NAME"]

# Initialiser le client Azure Blob Storage
blob_service_client = BlobServiceClient.from_connection_string(CONNECTION_STRING)
container_client = blob_service_client.get_container_client(CONTAINER_NAME)

# Fonction pour charger les tâches depuis Azure Blob Storage
def load_tasks():
    try:
        blob_client = container_client.get_blob_client(BLOB_NAME)
        blob_data = blob_client.download_blob().readall()
        return json.loads(blob_data)
    except Exception as e:
        print(f"Erreur lors du chargement des tâches : {e}")
        return []

# Fonction pour sauvegarder les tâches dans Azure Blob Storage
def save_tasks(tasks):
    try:
        blob_client = container_client.get_blob_client(BLOB_NAME)
        blob_client.upload_blob(json.dumps(tasks), overwrite=True)
    except Exception as e:
        print(f"Erreur lors de la sauvegarde des tâches : {e}")

# Structure d'une tâche
def create_task(task_id, description, priority="Medium", due_date=None):
    return {
        "id": task_id,
        "description": description,
        "priority": priority,
        "due_date": due_date,
        "created_at": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "completed": False
    }

# Endpoint pour récupérer toutes les tâches
@app.route('/api/tasks', methods=['GET'])
def get_tasks():
    tasks = load_tasks()
    return jsonify(tasks)

# Endpoint pour ajouter une tâche
@app.route('/api/tasks', methods=['POST'])
def add_task():
    tasks = load_tasks()

    if not request.json or 'description' not in request.json:
        abort(400, description="La description de la tâche est requise.")

    task_id = len(tasks) + 1
    new_task = create_task(
        task_id=task_id,
        description=request.json['description'],
        priority=request.json.get('priority', 'Medium'),
        due_date=request.json.get('due_date')
    )
    tasks.append(new_task)
    save_tasks(tasks)

    return jsonify(new_task), 201

# Endpoint pour marquer une tâche comme terminée
@app.route('/api/tasks/<int:task_id>/complete', methods=['PUT'])
def complete_task(task_id):
    tasks = load_tasks()
    task = next((task for task in tasks if task['id'] == task_id), None)
    if not task:
        abort(404, description="Tâche non trouvée.")

    task['completed'] = True
    save_tasks(tasks)
    return jsonify(task)

# Endpoint pour supprimer une tâche
@app.route('/api/tasks/<int:task_id>', methods=['DELETE'])
def delete_task(task_id):
    tasks = load_tasks()
    task = next((task for task in tasks if task['id'] == task_id), None)
    if not task:
        abort(404, description="Tâche non trouvée.")

    tasks = [task for task in tasks if task['id'] != task_id]
    save_tasks(tasks)
    return jsonify({"message": "Tâche supprimée avec succès."})

# Endpoint pour la page d'accueil
@app.route('/')
def index():
    return "Bienvenue sur l'application de gestion de tâches!"

# Point d'entrée pour exécuter l'application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
