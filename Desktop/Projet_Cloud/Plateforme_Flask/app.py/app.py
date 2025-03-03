from flask import Flask, jsonify, request, abort
import os
from datetime import datetime

# Initialisation de l'application Flask
app = Flask(__name__)

# Liste de tâches en mémoire (simulée)
tasks = []

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
    """
    Récupère la liste complète des tâches.
    """
    return jsonify(tasks)

# Endpoint pour ajouter une tâche
@app.route('/api/tasks', methods=['POST'])
def add_task():
    """
    Ajoute une nouvelle tâche à la liste.
    """
    if not request.json or not 'description' in request.json:
        abort(400, description="La description de la tâche est requise.")

    # Crée une nouvelle tâche
    task_id = len(tasks) + 1
    new_task = create_task(
        task_id=task_id,
        description=request.json['description'],
        priority=request.json.get('priority', 'Medium'),
        due_date=request.json.get('due_date')
    )
    tasks.append(new_task)

    return jsonify(new_task), 201

# Endpoint pour marquer une tâche comme terminée
@app.route('/api/tasks/<int:task_id>/complete', methods=['PUT'])
def complete_task(task_id):
    """
    Marque une tâche comme terminée.
    """
    task = next((task for task in tasks if task['id'] == task_id), None)
    if not task:
        abort(404, description="Tâche non trouvée.")

    task['completed'] = True
    return jsonify(task)

# Endpoint pour supprimer une tâche
@app.route('/api/tasks/<int:task_id>', methods=['DELETE'])
def delete_task(task_id):
    """
    Supprime une tâche de la liste.
    """
    global tasks
    task = next((task for task in tasks if task['id'] == task_id), None)
    if not task:
        abort(404, description="Tâche non trouvée.")

    tasks = [task for task in tasks if task['id'] != task_id]
    return jsonify({"message": "Tâche supprimée avec succès."})

# Endpoint pour la page d'accueil
@app.route('/')
def index():
    """
    Affiche une page d'accueil simple.
    """
    return "Bienvenue sur l'application de gestion de tâches!"

# Point d'entrée pour exécuter l'application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)