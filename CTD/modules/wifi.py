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
            'Name': "wifi",
            'Authors': [
                'Ivan Nikolskiy (enty8080) - module developer'
            ],
            'Description': "Set device wifi service state.",
            'Usage': "wifi <on|off>",
            'MinArgs': 1,
            'NeedsRoot': False
        })

    def run(self, argc, argv):
        if argv[1] in ['on', 'off']:
            if argv[1] == 'on':
                self.device.send_command("svc wifi enable")
            else:
                self.device.send_command("svc wifi disable")
        else:
            self.print_empty(f"Usage: {self.details['Usage']}")
