pipeline {
    agent none
    triggers {
        githubPush()  // This line triggers the job on a push to GitHub
    }
    stages {
        stage('build and test') {
            matrix {
                when {
                    anyOf {
                        branch 'main'
                        branch 'dev'
                        branch 'RT-45-new-cicd'
                    }
                }
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
                                filename "${PLATFORM == 'linux' ? 'DockerfileLinux' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh 'cmake -S . -B build'
                                    sh 'cmake --build build --config Release -j 8'
                                } else {
                                    bat '.\\build.bat'
                                }
                            }
                        }
                    }
                    stage('test') {
                        agent {
                            dockerfile {
                                filename "${PLATFORM == 'linux' ? 'DockerfileLinux' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh './build/proj'
                                } else {
                                    bat '.\\build\\Release\\proj.exe'
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
