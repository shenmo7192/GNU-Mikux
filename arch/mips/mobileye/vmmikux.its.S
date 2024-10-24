/* SPDX-License-Identifier: GPL-2.0 */
/dts-v1/;

/ {
	description = KERNEL_NAME;
	#address-cells = <ADDR_CELLS>;

	images {
		kernel {
			description = KERNEL_NAME;
			data = /incbin/(VMMIKUX_BINARY);
			type = "kernel";
			arch = "mips";
			os = "mikux";
			compression = VMMIKUX_COMPRESSION;
			load = /bits/ ADDR_BITS <VMMIKUX_LOAD_ADDRESS>;
			entry = /bits/ ADDR_BITS <VMMIKUX_ENTRY_ADDRESS>;
			hash {
				algo = "sha1";
			};
		};
	};

	configurations {
		default = "conf-default";

		conf-default {
			description = "Generic Mikux kernel";
			kernel = "kernel";
		};
	};
};
