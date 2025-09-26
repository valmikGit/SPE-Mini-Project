pipeline {
    agent any

    environment {
        DOCKERHUB_CREDS = credentials('dockerhub-creds')  // Jenkins credentials (username + password)
        IMAGE_NAME = "spe_mini_calculator"
        IMAGE_TAG = "latest"
        DOCKER_IMAGE = "${DOCKERHUB_CREDS_USR}/${IMAGE_NAME}:${IMAGE_TAG}"
    }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/valmikGit/SPE-Mini-Project.git'
            }
        }

        stage('Build') {
            steps {
                sh 'make clean && make'
            }
        }

        stage('Test') {
            steps {
                sh 'make test'
            }
        }

        stage('Docker Build') {
            steps {
                sh "docker build -t ${DOCKER_IMAGE} ."
            }
        }

        stage('Push Docker Image') {
            steps {
                sh "echo ${DOCKERHUB_CREDS_PSW} | docker login -u ${DOCKERHUB_CREDS_USR} --password-stdin"
                sh "docker push ${DOCKER_IMAGE}"
            }
        }

        stage('Deploy with Ansible') {
            steps {
                sh 'ansible-playbook -i "ansible/inventory" ansible/playbook.yml'
            }
        }
    }
}