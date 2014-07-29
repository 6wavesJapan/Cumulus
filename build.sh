#!/bin/bash

pushd CumulusLib
  make
popd

pushd CumulusServer
  make
popd
