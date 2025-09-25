#!/usr/bin/env bash
docker ps -q --filter "name=scientific_calculator" | xargs -r docker stop