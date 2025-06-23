pipeline {
    agent any

    stages {
        stage('Build Docker Image') {
            steps {
                sh 'docker build -t textreader-ci -f Dockerfile.jenkins .'
            }
        }

        stage('Run Headless Test') {
            steps {
                sh '''
                    docker run --rm -v "$PWD:/workspace" textreader-ci /bin/bash -c "
                        cp /workspace/entrypoint.sh /app &&
                        chmod +x /app/entrypoint.sh &&
                        /app/entrypoint.sh
                    "
                '''
            }
        }

        stage('Archive Screenshot') {
            steps {
                archiveArtifacts artifacts: 'screenshot-latest.png', fingerprint: true
            }
        }

        stage('Upload Code Coverage') {
            steps {
                withCredentials([string(credentialsId: 'CODECOV_TOKEN', variable: 'CODECOV_TOKEN')]) {
                    archiveArtifacts artifacts: 'coverage.info', fingerprint: true
                    sh '''
                        curl -Os https://uploader.codecov.io/latest/linux/codecov && \
                        chmod +x codecov && \
                        ./codecov -f coverage.info -t $CODECOV_TOKEN || echo "Codecov upload failed"
                    '''
                }
            }
        }
    }
}
