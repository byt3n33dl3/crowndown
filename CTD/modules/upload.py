"""
This module requires CTD: https://github.com/EntySec/CTD
Current source: https://github.com/EntySec/CTD
"""

import os

from CTD.lib.module import Module


class CTDModule(Module):
    def __init__(self):
        super().__init__()

        self.details.update({
            'Category': "manage",
            'Name': "upload",
            'Authors': [
                'Ivan Nikolskiy (enty8080) - module developer'
            ],
            'Description': "Upload file to device.",
            'Usage': "upload <local_file> <remote_path>",
            'MinArgs': 2,
            'NeedsRoot': False
        })

    def run(self, argc, argv):
        self.device.upload(argv[1], argv[2])
