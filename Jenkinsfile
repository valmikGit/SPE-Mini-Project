// Ensure webhook triggers work even for declarative pipelines
properties([
    pipelineTriggers([
        [$class: 'GitHubPushTrigger']
    ])
])

pipeline {
    agent any

    environment {
        DOCKERHUB_CREDENTIALS = 'dockerhub-creds' // Jenkins credential ID
        IMAGE_TAG = "latest"
        DOCKER_IMAGE = "scientific-calculator"
    }

    stages {
        stage('Checkout') {
            steps {
                // Use SCM defined in the job (Pipeline script from SCM)
                checkout scm
            }
        }

        stage('Build') {
            steps {
                sh 'make build'
            }
        }

        stage('Test') {
            steps {
                sh 'make test'
            }
        }

        stage('Docker Build') {
            steps {
                withCredentials([usernamePassword(credentialsId: env.DOCKERHUB_CREDENTIALS, usernameVariable: 'DOCKER_USER', passwordVariable: 'DOCKER_PASS')]) {
                    script {
                        def imageName = "${env.DOCKER_USER}/${env.DOCKER_IMAGE}:${env.IMAGE_TAG}"
                        sh "make docker-build DOCKERHUB_USER=${env.DOCKER_USER} IMAGE_TAG=${env.IMAGE_TAG}"
                    }
                }
            }
        }

        stage('Docker Push') {
            steps {
                withCredentials([usernamePassword(credentialsId: env.DOCKERHUB_CREDENTIALS, usernameVariable: 'DOCKER_USER', passwordVariable: 'DOCKER_PASS')]) {
                    sh 'echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin'
                    sh "make docker-push DOCKERHUB_USER=$DOCKER_USER IMAGE_TAG=${env.IMAGE_TAG}"
                }
            }
        }

        stage('Deploy via Ansible') {
            steps {
                withCredentials([usernamePassword(credentialsId: env.DOCKERHUB_CREDENTIALS, usernameVariable: 'DOCKER_USER', passwordVariable: 'DOCKER_PASS')]) {
                    sh 'ansible-playbook -i inventory.ini playbook-deploy.yml --extra-vars "docker_user=${DOCKER_USER} image_tag=${IMAGE_TAG}"'
                }
            }
        }
    }

    post {
        always {
            sh 'docker logout || true'
        }
    }
}