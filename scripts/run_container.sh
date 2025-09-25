#!/usr/bin/env bash
# Usage: ./run_container.sh <docker_user> [tag]
USER=${1:-youruser}
TAG=${2:-latest}
IMAGE="${USER}/scientific-calculator:${TAG}"
docker run --rm -it ${IMAGE}