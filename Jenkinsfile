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
                    docker run --rm -v "$PWD:/output" textreader-ci /bin/bash -c "
                        cd /output &&
                        ./entrypoint.sh &&  # replace with your actual test runner
                        gcovr -r . --xml-pretty -o coverage.xml &&
                        LATEST=$(ls -1t screenshot_*.png | head -n 1) &&
                        cp $LATEST screenshot-latest.png
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
