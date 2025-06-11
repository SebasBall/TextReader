pipeline {
    agent any
    stages {
        stage('Clonar repositorio') {
            steps {
                git 'https://github.com/SebasBall/TextReader.git'
            }
        }
        stage('Simular pruebas') {
            steps {
                echo 'Pruebas simuladas...'
            }
        }
        stage('Empaquetar') {
            steps {
                echo 'Empaquetado del proyecto completado.'
            }
        }
    }
    post {
        always {
            echo 'Pipeline terminado.'
        }
    }
}
