pipeline {
    agent any
    stages {
        stage('Docker') {
            agent {
              docker {
                image 'itkdev/php7.2-fpm:latest'
                args '-v $HOME/.composer-cache:/.composer:rw'
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
                        sh 'mkdir ./phan'
                        sh 'vendor/bin/phan --directory=. --allow-polyfill-parser --output-mode checkstyle --progress-bar --output ./phan/checkstyle-result.xml'
                    }
                }
            }
            post {
               always {
                    recordIssues enabledForFailure: true, tool: checkStyle()
                    recordIssues enabledForFailure: true, tool: spotBugs()
                }
            }
        }
        stage('Deployment') {
            steps {
               echo 'Hello world'
               sh "ansible srvitkphp56 -m shell -a 'uname -a'"
            }
        }
    }
}
