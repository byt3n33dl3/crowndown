"""
This module requires CTD: https://github.com/EntySec/CTD
Current source: https://github.com/EntySec/CTD
"""

from CTD.lib.module import Module


class CTDModule(Module):
    def __init__(self):
        super().__init__()

        self.details.update({
            'Category': "settings",
            'Name': "battery",
            'Authors': [
                'Ivan Nikolskiy (enty8080) - module developer'
            ],
            'Description': "Show device battery information.",
            'Usage': "battery",
            'MinArgs': 0,
            'NeedsRoot': False
        })

    def run(self, argc, argv):
        self.print_process("Getting battery information...")

        output = self.device.send_command("dumpsys battery")
        self.print_empty(output)
