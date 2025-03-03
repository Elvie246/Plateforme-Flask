from flask import Flask, jsonify, request
import json

app = Flask(__name__)

# Exemple de données statiques (ici, une base de données simulée)
tasks = [
    {"id": 1, "title": "Faire les courses", "description": "Acheter du pain, des légumes", "due_date": "2025-02-10", "status": "en cours"},
    {"id": 2, "title": "Réunion avec l'équipe", "description": "Discuter du projet Flask", "due_date": "2025-02-07", "status": "terminé"}
]

# Récupérer toutes les tâches
@app.route('/api/tasks', methods=['GET'])
def get_tasks():
    return jsonify(tasks)

# Récupérer une tâche par ID
@app.route('/api/tasks/<int:id>', methods=['GET'])
def get_task(id):
    task = next((task for task in tasks if task['id'] == id), None)
    if task is None:
        return jsonify({"message": "Tâche non trouvée"}), 404
    return jsonify(task)

# Créer une nouvelle tâche
@app.route('/api/tasks', methods=['POST'])
def create_task():
    new_task = request.get_json()
    new_task["id"] = len(tasks) + 1  # Assigner un ID unique
    tasks.append(new_task)
    return jsonify(new_task), 201

# Mettre à jour une tâche
@app.route('/api/tasks/<int:id>', methods=['PUT'])
def update_task(id):
    task = next((task for task in tasks if task['id'] == id), None)
    if task is None:
        return jsonify({"message": "Tâche non trouvée"}), 404
    updated_task = request.get_json()
    task.update(updated_task)
    return jsonify(task)

# Supprimer une tâche
@app.route('/api/tasks/<int:id>', methods=['DELETE'])
def delete_task(id):
    task = next((task for task in tasks if task['id'] == id), None)
    if task is None:
        return jsonify({"message": "Tâche non trouvée"}), 404
    tasks.remove(task)
    return jsonify({"message": "Tâche supprimée"}), 200

if __name__ == '__main__':
    app.run(debug=True)
