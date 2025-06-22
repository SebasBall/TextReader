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

                        CDA_DIR=$(find /app -type f -name '*.gcda' -exec dirname {} \\; | sort -u | head -n 1) && \
                        if [ -n \\"$GCDA_DIR\\" ]; then
                            echo 'Found coverage data in' \\"$GCDA_DIR\\"
                            lcov --capture --directory \\"$GCDA_DIR\\" --output-file /workspace/coverage.info
                        else
                            echo 'WARNING: No .gcda files found. Skipping coverage capture.'
                        fi &&

                        LATEST=$(ls -1t /workspace/screenshot_*.png 2>/dev/null | head -n 1) && \
                        [ -n "$LATEST" ] && cp "$LATEST" /workspace/screenshot-latest.png || \
                        echo "No screenshot found to copy."
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
            archiveArtifacts artifacts: 'coverage.info', fingerprint: true
             sh '''
                bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov upload failed"
                '''
            }
        }
    }
}
