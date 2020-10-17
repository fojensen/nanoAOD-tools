#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
    Example:
        python HiggsAnalysis/friend-tree-producer/scripts/electronScaleFactorProducer.py \
            --input /pnfs/desy.de/cms/tier2/store/user/ohlushch/MSSM/merged/2017/VBFHToTauTauM125_RunIIFall17MiniAODv2_PU2017_13TeV_MINIAOD_powheg-pythia8_v1/VBFHToTauTauM125_RunIIFall17MiniAODv2_PU2017_13TeV_MINIAOD_powheg-pythia8_v1.root \
            --output-dir  /nfs/dust/cms/user/glusheno/afs/RWTH/KIT/FriendTreeProducer/CMSSW_10_2_14/src/outputs_emQCDWeights \
            --rooworkspace-file /nfs/dust/cms/user/glusheno/htt_scalefactors_legacy_2017.root \
            --start 0 --end 11 \
            --all-relevant-pipelines \
            --dry
"""
import os
import sys
import json
import yaml
import ROOT
import numpy
import copy
from array import array
import six
import argparse
import logging

logger = logging.getLogger()

# the two channels that contain electrons
channels = ["mt"]

pipelines = ["nominal"]


def setup_logging(output_file, level=logging.DEBUG):
    logger.setLevel(level)
    formatter = logging.Formatter("%(name)s - %(levelname)s - %(message)s")

    handler = logging.StreamHandler()
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    file_handler = logging.FileHandler(output_file, "w")
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)


def parse_arguments():
    parser = argparse.ArgumentParser(
        description="create friend trees for electron scale factors form a given RooWorkspace"
    )
    parser.add_argument("--input", required=True, type=str, help="Input file.")

    parser.add_argument(
        "--tree", default="ntuple", type=str, help="Name of the root tree."
    )
    parser.add_argument(
        "--enable-logging",
        action="store_true",
        help="Enable loggging for debug purposes.",
    )
    parser.add_argument(
        "--cmsswbase",
        default=os.environ["CMSSW_BASE"],
        help="Set path for to local cmssw for submission with Grid-Control",
    )

    parser.add_argument(
        "--first-entry",
        "--first_entry",
        "--start",
        default=0,
        type=int,
        help="Index of first event to process.",
    )
    parser.add_argument(
        "--last-entry",
        "--last_entry",
        "--end",
        default=-1,
        type=int,
        help="Index of last event to process.",
    )

    parser.add_argument(
        "--pipeline",
        "--pipelines",
        "--folder",
        nargs="?",
        default=None,
        type=str,
        help="Directory within rootfile.",
    )
    parser.add_argument(
        "--output-dir", type=str, default=".", help="Tag of output files."
    )

    parser.add_argument(
        "--rooworkspace-file",
        type=str,
        default=None,
        help="location of the Roo Workspace file",
    )
    parser.add_argument("--config", nargs="?", type=str, default=None, help="Config")

    # parser.add_argument('--from-histograms', action='store_true', default=False, help='determine fractions')
    parser.add_argument("--dry", action="store_true", default=False, help="dry run")
    #parser.add_argument('--all-relevant-pipelines', action='store_true', default=False, help=' use all relevant piplelines')

    return parser.parse_args()


def apply_with_hist():
    pass


#def filter_data_channels(channels, datafile):
#    if "SingleElectron" in datafile or "_ElTau" in datafile:
#        channels = set(channels) & set(["et"])
##    elif "SingleElectron" in datafile or "_ElMu" in datafile:
##        channels = set(channels) & set(["em"])
#    else:
#        channels = set(channels) & set(["em", "et"])
#    return channels


def apply_with_rooworkspace(
    datafile,
    era,
    rooworkspace_file_name,
    outputfile,
    configpath,
    treename="ntuple",
    rootfilemode="read",
    eventrange=[0, -1],
    dry=False,
    channels=["mt"],
    pipelines=pipelines,
    all_relevant_pipelines=False,
):

    # filter channels
    #channels = filter_data_channels(channels, datafile)
    ## Use different SF for embedded samples
    #isEmbedded = True if "Embedding" in datafile else False
    isEmbedded = True

    config = yaml.load(open(configpath))
    if "rooworkspace" not in config.keys():
        raise Exception(
            "Config file %s has to contain key 'rooworkspace'!" % configpath
        )

    rootfilemode = rootfilemode.lower()
    if rootfilemode not in ["update", "recreate"] and not dry:
        raise Exception(
            "Mode %s not appropriate for create of ROOT file. Please choose from 'update' and 'recreate'"
            % rootfilemode
        )

    map_arguments = {}
    if "map_arguments" in config:
        map_arguments = config["map_arguments"]

    QCDFactorWorkspace = config["rooworkspace"]
    workspace_object_names = config["rooworkspace"].keys()
    #print "config: ", config

    # Reading rooworkspace file
    #print("rooworkspace_file_name: %s" % rooworkspace_file_name)
    rooworkspace_file = ROOT.TFile(rooworkspace_file_name, "read")
    # gSystem->AddIncludePath("-I$ROOFITSYS/include");
    m_workspace = rooworkspace_file.Get("w")
    m_functors = {}
    variables = set()
    #print "making functors"
    for object_name in workspace_object_names:
        print object_name
        m_functors[object_name] = {
            "function": m_workspace.function(config["rooworkspace"][object_name]["function"]),
            "argSet": m_workspace.argSet(",".join(config["rooworkspace"][object_name]["argSet"])),
            "arguments": config["rooworkspace"][object_name]["argSet"],
            "variables": config["rooworkspace"][object_name]["variables"],
        }

    #print "m_functors: ", m_functors

    # Prepare output
    if not dry:
        if not os.path.exists(os.path.dirname(outputfile)):
            os.makedirs(os.path.dirname(outputfile))
        output_file = ROOT.TFile(outputfile, rootfilemode)

    # Prepare data inputs
    input_file = ROOT.TFile(datafile, "READ")

    for channel in channels:
        if all_relevant_pipelines:
            pipelines = []
            for key in input_file.GetListOfKeys():
                if key.GetName().startswith(channel):
                    pipelines.append(
                        key.GetName().split("/")[0].replace(channel + "_", "")
                    )

        for pipeline in pipelines:
            #print "pipeline: ", pipeline
            pipeline = pipeline.replace(channel + "_", "")

            # Prepare data inputs
            #input_tree = input_file.Get("%s_%s/%s" % (channel, pipeline, treename))
            input_tree = input_file.Get("Events")
            # TODO: disable all variables that will not be needed for application with SetBranchStatus("*", 0)

            # Prepare dir
            if not dry:
                output_root_dir = output_file.mkdir("%s_%s" % (channel, pipeline))
                output_root_dir.cd()
                output_tree = ROOT.TTree(treename, treename)

            # Prepare branches
            output_buffer = {}
            for branch in m_functors.keys():
                output_buffer[branch] = array("d", [0])
                if not dry:
                    output_tree.Branch(branch, output_buffer[branch], "%s/D" % branch)
                    output_tree.SetBranchAddress(branch, output_buffer[branch])
            # Fill tree
            if eventrange[1] > 0:
                nev = eventrange[1] - eventrange[0] + 1
                if eventrange[1] >= input_tree.GetEntries():
                    raise Exception("The last entry exceeds maximum")
            else:
                nev = input_tree.GetEntries() - eventrange[0]
            printout_on = [eventrange[0] + i * int(nev / 10) for i in range(0, 11)]
            for evt_i, event in enumerate(input_tree):
                #print "****evt_i: ", evt_i
                if eventrange is not None:
                    if evt_i < eventrange[0]:
                        continue
                    elif (
                        evt_i > eventrange[1] and eventrange[1] >= 0
                    ):  # latter condition allows to set negative upper limit in order to have it ignored
                        break
                    elif evt_i in printout_on:
                        print(
                            "\t ...processing %d %% [Event %d]"
                            % (printout_on.index(evt_i) * 10, evt_i)
                        )

                 # Evaluating weights
                for ws_name in m_functors.keys():
                    #print "ws_name: ", ws_name
                    #print m_functors[ws_name]["argSet"]
                    #print m_functors[ws_name]["arguments"]
                    #print m_functors[ws_name]["variables"]
                  
                    for arg, var in zip(m_functors[ws_name]["arguments"], m_functors[ws_name]["variables"]):
                        #print "arg ", arg
                        #print "var ", var
                        m_functors[ws_name]["argSet"].setRealValue(arg, eval("event."+var))
                    output_buffer[ws_name][0] = m_functors[ws_name]["function"].getVal(m_functors[ws_name]["argSet"])
                    #print output_buffer[ws_name][0]
                if not dry:
                    output_tree.Fill()

            # Save
            if not dry:
                output_tree.Write()

    # Clean up
    rooworkspace_file.Close()
    input_file.Close()
    if not dry:
        output_file.Close()
    return 0


def main(args):
    print(args)
    nickname = os.path.basename(args.input).replace(".root", "")
    #channels = [args.pipeline.split("_")[0]]
    channels = ["mt"]
    # Get path to cmssw and fakefactordatabase
    cmsswbase = args.cmsswbase

    # Determine era
#    with open(
 #       cmsswbase
  #      + "/src/HiggsAnalysis/friend-tree-producer/data/input_params/datasets.json"
  #  ) as json_file:
  #      datasets = json.load(json_file)
    #era = str(datasets[nickname]["year"])
    era = "2018"

    # Create friend tree
    output_path = os.path.join(args.output_dir, nickname)
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    if args.rooworkspace_file is None:
        raise Exception("Rooworkspace file expected but not given")

    apply_with_rooworkspace(
        datafile=args.input,
        era=era,
        eventrange=[args.first_entry, args.last_entry],
        rooworkspace_file_name=args.rooworkspace_file,
        outputfile=os.path.join(
            output_path,
            "_".join(
                filter(
                    None,
                    [
                        nickname,
                        args.pipeline,
                        str(args.first_entry),
                        str(args.last_entry),
                    ],
                )
            )
            + ".root",
        ),
        configpath=args.config
        if args.config is not None
        else cmsswbase
        + "/src/HiggsAnalysis/friend-tree-producer/data/config_electronScaleFactorProducer_{}.yaml".format(era),
        treename=args.tree,
        rootfilemode="recreate" if not args.dry else "read",
        dry=args.dry,
        channels=channels,
        pipelines=pipelines if args.pipeline is None else [args.pipeline],
    )


if __name__ == "__main__":
    args = parse_arguments()

    if args.enable_logging:
        setup_logging(
            "electronScaleFactorProducer%s_%s_%s_%s.log"
            % (
                os.path.basename(args.input).replace(".root", ""),
                args.folder,
                args.first_entry,
                args.last_entry,
            ),
            logging.WARNING,
        )

    main(args)
