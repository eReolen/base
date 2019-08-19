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
                        sh 'vendor/bin/phan --allow-polyfill-parser --output-mode checkstyle --output checkstyle-result.xml'
                    }
                }
            }
            post {
                always {
                    recordIssues enabledForFailure: true, tool: checkStyle()
                }
            }
        }
        stage('Deployment') {
            parallel {
                stage('eReolen - develop') {
                    when {
                        branch 'develop'
                    }
                    steps {
                        // Deploy eReolen.
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs/sites/all/modules/ereol; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes updatedb'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolen_dk/htdocs; drush cache-clear all'"
                    }
                }
                stage('eReolenGo - develop') {
                    when {
                        branch 'develop'
                    }
                    steps {
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs/sites/all/modules/breol; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes updatedb'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/dev_ereolengo_dk/htdocs; drush cache-clear all'"
                    }
                }
                stage('eReolen - staging') {
                    when {
                        branch 'release'
                    }
                    steps {
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs/sites/all/modules/ereol; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs/sites/all/modules/ereol; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs/sites/all/modules/ereol; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs/sites/all/modules/ereol; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; drush --yes updatedb'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolen_dk/htdocs; drush cache-clear all'"
                    }
                }
                stage('eReolenGo - staging') {
                    when {
                        branch 'release'
                    }
                    steps {
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs/sites/all/modules/breol; git clean -d --force'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs/sites/all/modules/breol; git checkout ${BRANCH_NAME}'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs/sites/all/modules/breol; git fetch'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs/sites/all/modules/breol; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; drush --yes updatedb'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible devereolen -m shell -a 'cd /home/deploy/www/stg_ereolengo_dk/htdocs; drush cache-clear all'"
                    }
                }
                stage('eReolen - production') {
                    when {
                        branch 'master'
                    }
                    steps {
                        timeout(time: 30, unit: 'MINUTES') {
                            input 'Should the site be deployed?'
                        }
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; git clean -d --force'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; git fetch'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs/sites/all/modules/ereol; git clean -d --force'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs/sites/all/modules/ereol; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs/sites/all/modules/ereol; git fetch'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs/sites/all/modules/ereol; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush --yes updatedb'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible ereolen -m shell -a 'cd /home/deploy/www/ereolen_dk/htdocs; drush cache-clear all'"
                    }
                }
                stage('eReolenGo - production') {
                    when {
                        branch 'master'
                    }
                    steps {
                        timeout(time: 30, unit: 'MINUTES') {
                            input 'Should the site be deployed?'
                        }
                        // Install on server one.
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git clean -d --force'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git fetch'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git clean -d --force'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git fetch'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git reset origin/${BRANCH_NAME} --hard'"

                        // Install on server two.
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git clean -d --force'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git fetch'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; git reset origin/${BRANCH_NAME} --hard'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git clean -d --force'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git checkout ${BRANCH_NAME}'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git fetch'"
                        sh "ansible ereolengo2 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs/sites/all/modules/breol; git reset origin/${BRANCH_NAME} --hard'"

                        // Update application an clear cache.
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush --yes updatedb'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush --yes features-revert-all'"
                        sh "ansible ereolengo1 -m shell -a 'cd /home/deploy/www/ereolengo_dk/htdocs; drush cache-clear all'"
                    }
                }
            }
        }
    }
    post {
        always {
            script {
                slackNotifier(currentBuild.currentResult)
            }

            // Clean up our workspace
            cleanWs()
            deleteDir()
        }
    }
}
