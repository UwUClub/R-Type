pipeline {
    agent none  // This allows us to specify agents per stage
    stages {
        stage('build and test') {
            matrix {
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'linux', 'windows'
                    }
                }
                stages {
                    stage('build') {
                        agent {
                            dockerfile {
                                filename "${PLATFORM == 'linux' ? 'Dockerfile' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh 'cmake -S . -B build'
                                    sh 'cmake --build build'
                                } else {
                                    bat 'cmake -S . -B build'
                                    bat 'cmake --build build'
                                }
                            }
                        }
                    }
                    stage('test') {
                        agent {
                            dockerfile {
                                filename "${PLATFORM == 'linux' ? 'Dockerfile' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh './build/test/tests'
                                } else {
                                    bat '.\\build\\test\\tests.exe'
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
