@Library('jenkins-pipeline')_

pipeline {
    agent any
    stages {
        stage('Docker') {
            agent {
                docker {
                    image 'itkdev/php7.2-fpm:latest' /* 7.2 is used as phan only runs with this version */
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
                        sh 'vendor/bin/phan --directory=. --allow-polyfill-parser --output-mode checkstyle --progress-bar --output checkstyle-result.xml'
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
                // Deploy eReolen.
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes updatedb'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush cache-clear all'"
                // Deploy eReolen Go.
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes updatedb'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush cache-clear all'"
            }
        }
        stage('Deployment staging') {
            when {
                branch 'release'
            }
            steps {
                // Deploy eReolen.
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes updatedb'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush cache-clear all'"
                // Deploy eReolen Go.
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git pull'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes updatedb'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush cache-clear all'"
            }
        }
        stage('Deployment production') {
            when {
                branch 'master'
                tag '*'
            }
            steps {
                timeout(time: 30, unit: 'MINUTES') {
                    input 'Should the site be deployed?'
                }
                // Deploy eReolen.
                sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; git pull'"
                sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs/sites/all/modules/ereol; git pull'"
                sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush --yes updatedb'"
                sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush cache-clear all'"
                // Deploy eReolen Go.
                sh "ansible ereolengo -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git pull'"
                sh "ansible ereolengo -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git pull'"
                sh "ansible ereolengo -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush --yes updatedb'"
                sh "ansible ereolengo -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush --yes features-revert-all'"
                sh "ansible ereolengo -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush cache-clear all'"
            }
        }
    }
    post {
        always {
              echo "Pipeline result: ${currentBuild.currentResult}"
//            slackNotifier currentBuild.currentResult

            // Clean up our workspace
            cleanWs()
            deleteDir()
        }
    }
}
