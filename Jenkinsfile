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
                    docker run --rm -v "$PWD:/app" textreader-ci \
                    bash -c "
                        mkdir -p /app/output && \
                        ./your-executable && \
                        LATEST=\\$(ls -1t screenshot_*.png | head -n 1) && \
                        cp \\$LATEST /app/output/screenshot-latest.png && \
                        lcov --capture --directory . --output-file /app/output/coverage.info && \
                        lcov --remove /app/output/coverage.info '/usr/*' '*/Qt/*' --output-file /app/output/coverage.cleaned.info
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
