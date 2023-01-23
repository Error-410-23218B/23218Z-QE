import sys
import plotly.graph_objects as go
import time
from dash import Dash,html,dcc

app = Dash(__name__)

    

time = 0
isetpoint = (float(sys.stdin.readline())).append()
process_variable = float(sys.stdin.readline()).append
integral = (float(sys.stdin.readline())).append
prevError = (float(sys.stdin.readline())).append
derivative = (float(sys.stdin.readline())).append
Power = (float(sys.stdin.readline())).append
kP = float(sys.stdin.readline()).append
kI = float(sys.stdin.readline()).append
kD = float(sys.stdin.readline()).append

fig = go.Figure()
fig1 = fig.add_trace(go.Scatter(x=1, y=1,
                        mode='lines+markers',
                        name='lines+markers'))
fig2 = fig.add_trace(go.Scatter(x=time, y=process_variable,
                        mode='lines+markers',
                        name='lines+markers'))
fig3 = fig.add_trace(go.Scatter(x=time, y=integral,
                        mode='lines+markers',
                        name='lines+markers'))
fig4 = fig.add_trace(go.Scatter(x=time, y=derivative,
                        mode='lines+markers',
                        name='lines+markers'))
fig5 = fig.add_trace(go.Scatter(x=time, y=Power,
                        mode='lines+markers',
                        name='lines+markers'))
fig6 = fig.add_trace(go.Scatter(x=time, y=kP,
                        mode='lines+markers',
                        name='lines+markers'))
fig7 = fig.add_trace(go.Scatter(x=time, y=kI,
                        mode='lines+markers',
                        name='lines+markers'))
fig8 = fig.add_trace(go.Scatter(x=time, y=kD,
                        mode='lines+markers',
                        name='lines+markers'))
fig9 = fig.add_trace(go.Scatter(x=time, y=prevError,
                        mode='lines+markers',
                        name='lines+markers'))

app.layout = html.Div(children=[
    html.H1(children='Hello Dash'),

    html.Div(children='''
        Dash: A web application framework for your data.
    '''),

    dcc.Graph(
        id='setpoint-graph',
        figure=fig1
    )
])        

if __name__ == '__main__':
    app.run_server(debug=True)



    


