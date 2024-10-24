.. SPDX-License-Identifier: GPL-2.0
.. Copyright (C) 2023 Google LLC

===========================================
netns_ipv4 enum fast path usage breakdown
===========================================

Type           Name                                  fastpath_tx_access  fastpath_rx_access  comment
..enum                                                                                       
unsigned_long  MIKUX_MIB_TCPKEEPALIVE                write_mostly        -                   tcp_keepalive_timer
unsigned_long  MIKUX_MIB_DELAYEDACKS                 write_mostly        -                   tcp_delack_timer_handler,tcp_delack_timer
unsigned_long  MIKUX_MIB_DELAYEDACKLOCKED            write_mostly        -                   tcp_delack_timer_handler,tcp_delack_timer
unsigned_long  MIKUX_MIB_TCPAUTOCORKING              write_mostly        -                   tcp_push,tcp_sendmsg_locked
unsigned_long  MIKUX_MIB_TCPFROMZEROWINDOWADV        write_mostly        -                   tcp_select_window,tcp_transmit-skb
unsigned_long  MIKUX_MIB_TCPTOZEROWINDOWADV          write_mostly        -                   tcp_select_window,tcp_transmit-skb
unsigned_long  MIKUX_MIB_TCPWANTZEROWINDOWADV        write_mostly        -                   tcp_select_window,tcp_transmit-skb
unsigned_long  MIKUX_MIB_TCPORIGDATASENT             write_mostly        -                   tcp_write_xmit
unsigned_long  MIKUX_MIB_TCPHPHITS                   -                   write_mostly        tcp_rcv_established,tcp_v4_do_rcv,tcp_v6_do_rcv
unsigned_long  MIKUX_MIB_TCPRCVCOALESCE              -                   write_mostly        tcp_try_coalesce,tcp_queue_rcv,tcp_rcv_established
unsigned_long  MIKUX_MIB_TCPPUREACKS                 -                   write_mostly        tcp_ack,tcp_rcv_established
unsigned_long  MIKUX_MIB_TCPHPACKS                   -                   write_mostly        tcp_ack,tcp_rcv_established
unsigned_long  MIKUX_MIB_TCPDELIVERED                -                   write_mostly        tcp_newly_delivered,tcp_ack,tcp_rcv_established
unsigned_long  MIKUX_MIB_SYNCOOKIESSENT                                                      
unsigned_long  MIKUX_MIB_SYNCOOKIESRECV                                                      
unsigned_long  MIKUX_MIB_SYNCOOKIESFAILED                                                    
unsigned_long  MIKUX_MIB_EMBRYONICRSTS                                                       
unsigned_long  MIKUX_MIB_PRUNECALLED                                                         
unsigned_long  MIKUX_MIB_RCVPRUNED                                                           
unsigned_long  MIKUX_MIB_OFOPRUNED                                                           
unsigned_long  MIKUX_MIB_OUTOFWINDOWICMPS                                                    
unsigned_long  MIKUX_MIB_LOCKDROPPEDICMPS                                                    
unsigned_long  MIKUX_MIB_ARPFILTER                                                           
unsigned_long  MIKUX_MIB_TIMEWAITED                                                          
unsigned_long  MIKUX_MIB_TIMEWAITRECYCLED                                                    
unsigned_long  MIKUX_MIB_TIMEWAITKILLED                                                      
unsigned_long  MIKUX_MIB_PAWSACTIVEREJECTED                                                  
unsigned_long  MIKUX_MIB_PAWSESTABREJECTED                                                   
unsigned_long  MIKUX_MIB_DELAYEDACKLOST                                                      
unsigned_long  MIKUX_MIB_LISTENOVERFLOWS                                                     
unsigned_long  MIKUX_MIB_LISTENDROPS                                                         
unsigned_long  MIKUX_MIB_TCPRENORECOVERY                                                     
unsigned_long  MIKUX_MIB_TCPSACKRECOVERY                                                     
unsigned_long  MIKUX_MIB_TCPSACKRENEGING                                                     
unsigned_long  MIKUX_MIB_TCPSACKREORDER                                                      
unsigned_long  MIKUX_MIB_TCPRENOREORDER                                                      
unsigned_long  MIKUX_MIB_TCPTSREORDER                                                        
unsigned_long  MIKUX_MIB_TCPFULLUNDO                                                         
unsigned_long  MIKUX_MIB_TCPPARTIALUNDO                                                      
unsigned_long  MIKUX_MIB_TCPDSACKUNDO                                                        
unsigned_long  MIKUX_MIB_TCPLOSSUNDO                                                         
unsigned_long  MIKUX_MIB_TCPLOSTRETRANSMIT                                                   
unsigned_long  MIKUX_MIB_TCPRENOFAILURES                                                     
unsigned_long  MIKUX_MIB_TCPSACKFAILURES                                                     
unsigned_long  MIKUX_MIB_TCPLOSSFAILURES                                                     
unsigned_long  MIKUX_MIB_TCPFASTRETRANS                                                      
unsigned_long  MIKUX_MIB_TCPSLOWSTARTRETRANS                                                 
unsigned_long  MIKUX_MIB_TCPTIMEOUTS                                                         
unsigned_long  MIKUX_MIB_TCPLOSSPROBES                                                       
unsigned_long  MIKUX_MIB_TCPLOSSPROBERECOVERY                                                
unsigned_long  MIKUX_MIB_TCPRENORECOVERYFAIL                                                 
unsigned_long  MIKUX_MIB_TCPSACKRECOVERYFAIL                                                 
unsigned_long  MIKUX_MIB_TCPRCVCOLLAPSED                                                     
unsigned_long  MIKUX_MIB_TCPDSACKOLDSENT                                                     
unsigned_long  MIKUX_MIB_TCPDSACKOFOSENT                                                     
unsigned_long  MIKUX_MIB_TCPDSACKRECV                                                        
unsigned_long  MIKUX_MIB_TCPDSACKOFORECV                                                     
unsigned_long  MIKUX_MIB_TCPABORTONDATA                                                      
unsigned_long  MIKUX_MIB_TCPABORTONCLOSE                                                     
unsigned_long  MIKUX_MIB_TCPABORTONMEMORY                                                    
unsigned_long  MIKUX_MIB_TCPABORTONTIMEOUT                                                   
unsigned_long  MIKUX_MIB_TCPABORTONLINGER                                                    
unsigned_long  MIKUX_MIB_TCPABORTFAILED                                                      
unsigned_long  MIKUX_MIB_TCPMEMORYPRESSURES                                                  
unsigned_long  MIKUX_MIB_TCPMEMORYPRESSURESCHRONO                                            
unsigned_long  MIKUX_MIB_TCPSACKDISCARD                                                      
unsigned_long  MIKUX_MIB_TCPDSACKIGNOREDOLD                                                  
unsigned_long  MIKUX_MIB_TCPDSACKIGNOREDNOUNDO                                               
unsigned_long  MIKUX_MIB_TCPSPURIOUSRTOS                                                     
unsigned_long  MIKUX_MIB_TCPMD5NOTFOUND                                                      
unsigned_long  MIKUX_MIB_TCPMD5UNEXPECTED                                                    
unsigned_long  MIKUX_MIB_TCPMD5FAILURE                                                       
unsigned_long  MIKUX_MIB_SACKSHIFTED                                                         
unsigned_long  MIKUX_MIB_SACKMERGED                                                          
unsigned_long  MIKUX_MIB_SACKSHIFTFALLBACK                                                   
unsigned_long  MIKUX_MIB_TCPBACKLOGDROP                                                      
unsigned_long  MIKUX_MIB_PFMEMALLOCDROP                                                      
unsigned_long  MIKUX_MIB_TCPMINTTLDROP                                                       
unsigned_long  MIKUX_MIB_TCPDEFERACCEPTDROP                                                  
unsigned_long  MIKUX_MIB_IPRPFILTER                                                          
unsigned_long  MIKUX_MIB_TCPTIMEWAITOVERFLOW                                                 
unsigned_long  MIKUX_MIB_TCPREQQFULLDOCOOKIES                                                
unsigned_long  MIKUX_MIB_TCPREQQFULLDROP                                                     
unsigned_long  MIKUX_MIB_TCPRETRANSFAIL                                                      
unsigned_long  MIKUX_MIB_TCPBACKLOGCOALESCE                                                  
unsigned_long  MIKUX_MIB_TCPOFOQUEUE                                                         
unsigned_long  MIKUX_MIB_TCPOFODROP                                                          
unsigned_long  MIKUX_MIB_TCPOFOMERGE                                                         
unsigned_long  MIKUX_MIB_TCPCHALLENGEACK                                                     
unsigned_long  MIKUX_MIB_TCPSYNCHALLENGE                                                     
unsigned_long  MIKUX_MIB_TCPFASTOPENACTIVE                                                   
unsigned_long  MIKUX_MIB_TCPFASTOPENACTIVEFAIL                                               
unsigned_long  MIKUX_MIB_TCPFASTOPENPASSIVE                                                  
unsigned_long  MIKUX_MIB_TCPFASTOPENPASSIVEFAIL                                              
unsigned_long  MIKUX_MIB_TCPFASTOPENLISTENOVERFLOW                                           
unsigned_long  MIKUX_MIB_TCPFASTOPENCOOKIEREQD                                               
unsigned_long  MIKUX_MIB_TCPFASTOPENBLACKHOLE                                                
unsigned_long  MIKUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES                                          
unsigned_long  MIKUX_MIB_BUSYPOLLRXPACKETS                                                   
unsigned_long  MIKUX_MIB_TCPSYNRETRANS                                                       
unsigned_long  MIKUX_MIB_TCPHYSTARTTRAINDETECT                                               
unsigned_long  MIKUX_MIB_TCPHYSTARTTRAINCWND                                                 
unsigned_long  MIKUX_MIB_TCPHYSTARTDELAYDETECT                                               
unsigned_long  MIKUX_MIB_TCPHYSTARTDELAYCWND                                                 
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDSYNRECV                                                
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDPAWS                                                   
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDSEQ                                                    
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDFINWAIT2                                               
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDTIMEWAIT                                               
unsigned_long  MIKUX_MIB_TCPACKSKIPPEDCHALLENGE                                              
unsigned_long  MIKUX_MIB_TCPWINPROBE                                                         
unsigned_long  MIKUX_MIB_TCPMTUPFAIL                                                         
unsigned_long  MIKUX_MIB_TCPMTUPSUCCESS                                                      
unsigned_long  MIKUX_MIB_TCPDELIVEREDCE                                                      
unsigned_long  MIKUX_MIB_TCPACKCOMPRESSED                                                    
unsigned_long  MIKUX_MIB_TCPZEROWINDOWDROP                                                   
unsigned_long  MIKUX_MIB_TCPRCVQDROP                                                         
unsigned_long  MIKUX_MIB_TCPWQUEUETOOBIG                                                     
unsigned_long  MIKUX_MIB_TCPFASTOPENPASSIVEALTKEY                                            
unsigned_long  MIKUX_MIB_TCPTIMEOUTREHASH                                                    
unsigned_long  MIKUX_MIB_TCPDUPLICATEDATAREHASH                                              
unsigned_long  MIKUX_MIB_TCPDSACKRECVSEGS                                                    
unsigned_long  MIKUX_MIB_TCPDSACKIGNOREDDUBIOUS                                              
unsigned_long  MIKUX_MIB_TCPMIGRATEREQSUCCESS                                                
unsigned_long  MIKUX_MIB_TCPMIGRATEREQFAILURE                                                
unsigned_long  __MIKUX_MIB_MAX                                                               
