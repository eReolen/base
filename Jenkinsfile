pipeline {
    agent any
    stages {
        stage('Docker') {
            agent {
                docker {
                    image 'itkdev/php7.2-fpm:latest'
                    args '-v /var/lib/jenkins/.composer-cache:/.composer:rw'
                }
            }
            stages {
                stage('Build') {
                    steps {
                        sh 'composer install'
                    }
                }
                stage('Analysis') {
                    steps {
                        sh 'vendor/bin/phan --directory=. --allow-polyfill-parser --output-mode checkstyle --progress-bar --output ./phan/checkstyle-result.xml'
                    }
                }
            }
            post {
                always {
                    recordIssues enabledForFailure: true, tool: checkStyle()
                    recordIssues enabledForFailure: true, tool: spotBugs()
                }
                success {
                     sh 'echo "This will run only if successful"'
                }
                failure {
                      sh 'echo "This will run only if failed"'
                }
            }
        }
        stage('Deployment develop') {
            when {
                branch 'develop'
            }
            steps {
                sh "ansible srvitkphp56 -m shell -a 'uname -a'"
            }
        }
        stage('Deployment production') {
            when {
                branch 'master'
            }
            steps {
                input message: 'Should the site be deployed?' ok: "Yes, 'Make it so'"
                sh "ansible srvitkphp56 -m shell -a 'uname -a'"
            }
        }
    }
}
