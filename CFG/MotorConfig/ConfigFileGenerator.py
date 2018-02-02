from xml.dom import minidom
from xml.etree.ElementTree import ElementTree,Element

workspace="../MotorConfig"

def read_xml(in_path):
    tree = ElementTree()
    tree.parse(in_path)
    return tree

def write_xml(tree, out_path):
    tree.write(out_path, encoding="utf-8", xml_declaration=True)

def if_match(node, kv_map):
    for key in kv_map:
        if node.get(key) != kv_map.get(key):
            return False
    return True

# ---------------search -----

def find_nodes(tree, path):
    return tree.findall(path)

def get_node_by_keyvalue(nodelist, kv_map):
    result_nodes = []
    for node in nodelist:
        if if_match(node, kv_map):
            result_nodes.append(node)
    return result_nodes

# ---------------change -----

def change_node_properties(nodelist, kv_map, is_delete=False):
    for node in nodelist:
        for key in kv_map:
            if is_delete:
                if key in node.attrib:
                    del node.attrib[key]
            else:
                node.set(key, kv_map.get(key))

def change_node_text(nodelist, text, is_add=False, is_delete=False):
    for node in nodelist:
        if is_add:
            node.text += text
        elif is_delete:
            node.text = ""
        else:
            node.text = text

def create_node(tag, property_map, content):
    element = Element(tag, property_map)
    element.text = content
    return element

def add_child_node(nodelist, element):
    for node in nodelist:
        node.append(element)

def del_node_by_tagkeyvalue(nodelist, tag, kv_map):
    for parent_node in nodelist:
        children = parent_node.getchildren()
        for child in children:
            if child.tag == tag and if_match(child, kv_map):
                parent_node.remove(child)

class ConfigFileGenerator():
    def __init__(self):
        self.id=0

    def LmFileGenerator(self,NodesMotorFile,NodesMusterFile):
        for i in range(20):
            #find the target properties
            result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.LmTable["+str(i)+"]"})
            value=result_nodes[0].attrib["Value"]
            #write in muster file#
            result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_LmTable" + str(i)})
            change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.LmRated"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_LmRated_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Llr_Min"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Llr_Min_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Llr_Max"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Llr_Max_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Lls_Min"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Lls_Min_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Lls_Max"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Lls_Max_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Lm100"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Lm100_H7"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.Im100"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_Im100_mArms"})
        change_node_properties(result_nodes, {"Value": value})

    def MotorFileGenerator(self,NodesMotorFile,NodesMusterFile):
        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.SpeedMax"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_SpeedMax_rpm1"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.EncPulses"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_EncPulses"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.FluxRated"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_FluxRated_mWb2"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.CurrentMax"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_CurrentMax_mArms"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.TorqueMax"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_TorqueMax_Nm3"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.CC_Gain"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_CC_Gain_pct2"})
        change_node_properties(result_nodes, {"Value": value})

    def CANFileGenerator(self,id,NodesMusterFile):
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANBasicNodeID"})
        change_node_properties(result_nodes, {"Value": str(id)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_EMCY_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 128)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_RPDO1_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 512)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_RSDO_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 1536)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_TPDO1_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 384)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_TPDO2_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 640)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_CANopen_TSDO_COB_ID"})
        change_node_properties(result_nodes, {"Value": str(id + 1408)})

    def TempSensorFileGenerator(self,NodesMotorFile,NodesMusterFile):
        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.RrBase"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_RrBase_Ohm6"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.TBase_r"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_TBase_r_C"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.TCoeff_r"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_TCoeff_r"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.RsBase"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_RsBase_Ohm6"})
        change_node_properties(result_nodes, {"Value": value})

        result_nodes = get_node_by_keyvalue(NodesMotorFile, {"ParameterName": "Motor.TBase_s"})
        value = result_nodes[0].attrib["Value"]
        # write in muster file#
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_MD_TBase_s_C"})
        change_node_properties(result_nodes, {"Value": value})


    def UserFileGenerator(self,UserDefine,NodesMusterFile):
        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_AcelMax"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['AcelMax']*10)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_DcelMax"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['DcelMax']*10)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_DcelSafeStopMax"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['DcelSafetyStopMax']*10)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_SpdMax_rpm1"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['MaxSpeed']*10)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_V_Nominal_mV"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['BatterieVolt']*1000)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_UnderVolt_mV"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['BatterieVolt']*400)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_UserTorqueLimit_pct2"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['UserTorqueLimit']*100)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_BrkSettlingValue_pct2"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['BrakeSettlingValue']*100)})

        result_nodes = get_node_by_keyvalue(NodesMusterFile, {"ParameterName": "EE_BrkSteadyValue_pct2"})
        change_node_properties(result_nodes, {"Value": str(UserDefine['BrakeSteadyValue']*100)})

    def run(self,motor_file,id,user_define):
        self.id=id
        tree_motorfile = read_xml(motor_file)
        tree_musterfile = read_xml("MusterFile.xml")
        nodes_motorfile = find_nodes(tree_motorfile, "PARAMETERITEM")
        nodes_musterfile = find_nodes(tree_musterfile, "PARAMETERITEM")

        self.LmFileGenerator(nodes_motorfile,nodes_musterfile)
        self.MotorFileGenerator(nodes_motorfile,nodes_musterfile)
        self.TempSensorFileGenerator(nodes_motorfile,nodes_musterfile)
        self.CANFileGenerator(id,nodes_musterfile)
        self.UserFileGenerator(user_define,nodes_musterfile)

        result_nodes = get_node_by_keyvalue(nodes_musterfile, {"NodeNr": "0,0"})
        change_node_properties(result_nodes, {"NodeNr": "0,"+str(self.id)})

        write_xml(tree_musterfile, "./UmrichterID" + str(id) + ".xml")


if __name__ == "__main__":
    a=ConfigFileGenerator()
    Config_File={"AcelMax" : 10000,
                 "DcelMax": 10000,
                 "DcelSafetyStopMax":10000,
                 "MaxSpeed": 3000,
                 "BatterieVolt": 48,
                 "UserTorqueLimit": 100,
                 "BrakeSettlingValue": 40,
                 "BrakeSteadyValue":30}


    a.run("motorfile.xml",9,Config_File)