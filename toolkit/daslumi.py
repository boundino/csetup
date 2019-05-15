## Ref: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile

#
from CRABClient.UserUtilities import config, getLumiListInValidFiles
from WMCore.DataStructs.LumiList import LumiList

import sys

argv_a = ''
argv_b = ''
if len(sys.argv) == 3:
	argv_a = sys.argv[1]
	argv_b = sys.argv[2]
elif len(sys.argv) == 2:
	argv_a = sys.argv[1]
else:
	print("Usage: python daslumi.py [dataset/json] [dataset/json].\n")
	optyn = ""
	while (optyn != "y" and optyn != "n"):
		optyn = raw_input("Would you want to run example [y/n]: ")
	if optyn == "y":
		argv_a = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt"
		argv_b = "/HIDoubleMuonPsiPeri/HIRun2018A-04Apr2019-v1/AOD"
		commandex = "\n`python daslumi.py " + argv_a + " " + argv_b + "`\n"
		print(commandex)
	else:
		sys.exit(1)

## argv_a >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
print("\n\033[1;32margv_a:\033[0m\033[3;32m"),
print(argv_a),
print("\033[0m")
if ".txt" in argv_a:
	lumimask_a = LumiList(filename = argv_a)
else:
	lumimask_a = getLumiListInValidFiles(dataset = argv_a, dbsurl = 'global')
print(lumimask_a)
## <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

if len(sys.argv) == 2:
	sys.exit(0)

## argv_b >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
print("\n\033[1;31margv_b:\033[0m\033[3;31m"),
print(argv_b),
print("\033[0m")
if ".txt" in argv_b:
	lumimask_b = LumiList(filename = argv_b)
else:
	lumimask_b = getLumiListInValidFiles(dataset = argv_b, dbsurl = 'global')
print(lumimask_b)
## <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

lumimask_ab = lumimask_a & lumimask_b
lumimask_aonly = lumimask_a - lumimask_b
lumimask_bonly = lumimask_b - lumimask_a

print("\033[0m\n\033[1;33m==== argv_a & argv_b:")
print("\033[0m\033[2;33m"),
print(lumimask_ab)

print("\033[0m\n\033[1;32m>>>> argv_a only:\033[0m\033[3;32m"),
print(argv_a)
print("\033[0m\033[2;32m"),
print(lumimask_aonly)

print("\033[0m\n\033[1;31m<<<< argv_b only:\033[0m\033[3;31m"),
print(argv_b)
print("\033[0m\033[2;31m"),
print(lumimask_bonly)

print("\033[0m")

# compareJSON.py --diff 
# newLumiMask.writeJSON('toprocess_v1.json')
