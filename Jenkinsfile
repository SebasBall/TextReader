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
                    docker run --rm -v "$PWD:/output" textreader-ci
                    LATEST=$(ls -1t screenshot_*.png | head -n 1)
                    cp "$LATEST" screenshot-latest.png
                    bash -c "
                        lcov --capture --directory . --output-file /output/coverage.info && \
                        cov --remove /output/coverage.info '/usr/*' '*/Qt/*' --output-file /output/coverage.cleaned.info
                        "
                '''
            }
        }

        stage('Archive Screenshot') {
            steps {
                archiveArtifacts artifacts: 'screenshot-latest.png', fingerprint: true
            }
        }

        stage('Upload to Codecov') {
            steps {
                sh '''
                    bash <(curl -s https://codecov.io/bash) -f coverage.cleaned.info
                '''
            }
        }

    }
}
