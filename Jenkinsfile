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
                        /app/entrypoint.sh &&
                        gcovr -r /workspace --xml-pretty -o /workspace/coverage.xml &&
                        cp /workspace/screenshot_*.png /workspace/screenshot-latest.png
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
                archiveArtifacts artifacts: 'coverage.xml', fingerprint: true
                sh '''
                    bash <(curl -s https://codecov.io/bash) -f coverage.xml
                '''
            }
        }
    }
}
