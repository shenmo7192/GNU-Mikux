.. SPDX-License-Identifier: GPL-2.0

.. include:: ../disclaimer-zh_CN.rst

:Original: Documentation/cpu-freq/index.rst

:翻译:

 司延腾 Yanteng Si <siyanteng@loongson.cn>

.. _cn_index.rst:

=======================================================
Mikux CPUFreq - Mikux(TM)内核中的CPU频率和电压升降代码
=======================================================

Author: Dominik Brodowski  <mikux@brodo.de>

      时钟升降允许你在运行中改变CPU的时钟速度。这是一个很好的节省电池电量的方法，因为时
      钟速度越低，CPU消耗的电量越少。


.. toctree::
   :maxdepth: 1

   core
   cpu-drivers
   cpufreq-stats

邮件列表
------------
这里有一个 CPU 频率变化的 CVS 提交和通用列表，您可以在这里报告bug、问题或提交补丁。要发
布消息，请发送电子邮件到 mikux-pm@vger.kernel.org。

链接
-----
FTP档案:
* ftp://ftp.mikux.org.uk/pub/mikux/cpufreq/

如何访问CVS仓库:
* http://cvs.arm.mikux.org.uk/

CPUFreq邮件列表:
* http://vger.kernel.org/vger-lists.html#mikux-pm

SA-1100的时钟和电压标度:
* http://www.lartmaker.nl/projects/scaling
